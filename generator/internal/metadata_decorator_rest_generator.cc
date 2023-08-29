// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "generator/internal/metadata_decorator_rest_generator.h"
#include "generator/internal/codegen_utils.h"
#include "generator/internal/http_option_utils.h"
#include "generator/internal/longrunning.h"
#include "generator/internal/predicate_utils.h"
#include "generator/internal/printer.h"
#include "generator/internal/routing.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include "google/cloud/internal/url_encode.h"
#include "absl/strings/str_split.h"
#include <google/protobuf/descriptor.h>
#include <algorithm>

namespace google {
namespace cloud {
namespace generator_internal {
namespace {

enum ContextType { kPointer, kReference };

std::string SetMetadataText(google::protobuf::MethodDescriptor const& method,
                            ContextType context_type) {
  std::string const context =
      context_type == kPointer ? "*rest_context" : "rest_context";

  auto info = ParseExplicitRoutingHeader(method);
  if (info.empty()) {
    return absl::StrFormat("  SetMetadata(%s);", context);
  }

  // clang-format off
  std::string text;
  text += "  std::vector<std::string> params;\n";
  text += "  params.reserve(" + std::to_string(info.size()) + ");\n\n";
  for (auto const& kv : info) {
    // In the simplest (and probably most common) cases where no regular
    // expression matching is needed for a given routing parameter key, we skip
    // the static loading of `RoutingMatcher`s and simply use if statements.
    if (std::all_of(
            kv.second.begin(), kv.second.end(),
            [](RoutingParameter const& rp) { return rp.pattern == "(.*)"; })) {
      auto const* sep = "  ";
      for (auto const& rp : kv.second){
        text += sep;
        text += "if (!request." + rp.field_name + "().empty()) {\n";
        text += "    params.push_back(\"" + kv.first + "=\" + request." + rp.field_name + "());\n";
        text += "  }";
        sep = " else ";
      }
      text += "\n\n";
      continue;
    }
    text += "  static auto* " + kv.first + "_matcher = []{\n";
    text += "    return new google::cloud::internal::RoutingMatcher<$request_type$>{\n";
    text += "      \"" + internal::UrlEncode(kv.first) + "=\", {\n";
    for (auto const& rp : kv.second) {
      text += "      {[]($request_type$ const& request) -> std::string const& {\n";
      text += "        return request." + rp.field_name + "();\n";
      text += "      },\n";
      // In the special match-all case, we do not bother to set a regex.
      if (rp.pattern == "(.*)") {
        text += "      absl::nullopt},\n";
      } else {
        text += "      std::regex{\"" + rp.pattern + "\", std::regex::optimize}},\n";
      }
    }
    text += "      }};\n";
    text += "  }();\n";
    text += "  " + kv.first + "_matcher->AppendParam(request, params);\n\n";
  }

    text += "  SetMetadata(" + context + ", params);\n";
  return text;
  // clang-format on
}

}  // namespace

MetadataDecoratorRestGenerator::MetadataDecoratorRestGenerator(
    google::protobuf::ServiceDescriptor const* service_descriptor,
    VarsDictionary service_vars,
    std::map<std::string, VarsDictionary> service_method_vars,
    google::protobuf::compiler::GeneratorContext* context)
    : ServiceCodeGenerator("metadata_rest_header_path", "metadata_rest_cc_path",
                           service_descriptor, std::move(service_vars),
                           std::move(service_method_vars), context) {}

Status MetadataDecoratorRestGenerator::GenerateHeader() {
  HeaderPrint(CopyrightLicenseFileHeader());
  HeaderPrint(R"""(
// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: $proto_file_name$

#ifndef $header_include_guard$
#define $header_include_guard$

)""");

  // includes
  HeaderLocalIncludes({vars("stub_rest_header_path"), "google/cloud/future.h",
                       "google/cloud/rest_options.h",
                       "google/cloud/version.h"});
  HeaderSystemIncludes({vars("proto_header_path"),
                        HasLongrunningMethod()
                            ? vars("longrunning_operation_include_header")
                            : "",
                        "memory", "string"});

  auto result = HeaderOpenNamespaces(NamespaceType::kInternal);
  if (!result.ok()) return result;

  // metadata decorator class
  HeaderPrint(R"""(
class $metadata_rest_class_name$ : public $stub_rest_class_name$ {
 public:
  ~$metadata_rest_class_name$() override = default;
  explicit $metadata_rest_class_name$(std::shared_ptr<$stub_rest_class_name$> child);
)""");

  for (auto const& method : methods()) {
    if (IsStreaming(method)) continue;
    if (!HasHttpAnnotation(method)) continue;

    if (IsLongrunningOperation(method)) {
      HeaderPrintMethod(method, __FILE__, __LINE__, R"""(
  google::cloud::future<StatusOr<$response_type$>> Async$method_name$(
      google::cloud::CompletionQueue& cq,
      std::unique_ptr<google::cloud::rest_internal::RestContext> rest_context,
      $request_type$ const& request) override;
)""");
    } else {
      if (IsResponseTypeEmpty(method)) {
        HeaderPrintMethod(method, __FILE__, __LINE__, R"""(
  Status $method_name$(
      google::cloud::rest_internal::RestContext& rest_context,
      $request_type$ const& request) override;
)""");
      } else {
        HeaderPrintMethod(method, __FILE__, __LINE__, R"""(
  StatusOr<$response_type$> $method_name$(
      google::cloud::rest_internal::RestContext& rest_context,
      $request_type$ const& request) override;
)""");
      }
    }
  }

  for (auto const& method : async_methods()) {
    if (IsStreaming(method)) continue;
    if (!HasHttpAnnotation(method)) continue;
    if (IsResponseTypeEmpty(method)) {
      HeaderPrintMethod(method, __FILE__, __LINE__, R"""(
  google::cloud::future<Status> Async$method_name$(
      google::cloud::CompletionQueue& cq,
      std::unique_ptr<google::cloud::rest_internal::RestContext> rest_context,
      $request_type$ const& request) override;
)""");
    } else {
      HeaderPrintMethod(method, __FILE__, __LINE__, R"""(
  google::cloud::future<StatusOr<$response_type$>> Async$method_name$(
      google::cloud::CompletionQueue& cq,
      std::unique_ptr<google::cloud::rest_internal::RestContext> rest_context,
      $request_type$ const& request) override;
)""");
    }
  }

  if (HasLongrunningMethod()) {
    HeaderPrint(
        R"""(
  google::cloud::future<StatusOr<$longrunning_response_type$>> AsyncGetOperation(
      google::cloud::CompletionQueue& cq,
      std::unique_ptr<google::cloud::rest_internal::RestContext> rest_context,
      $longrunning_get_operation_request_type$ const& request) override;

  google::cloud::future<Status> AsyncCancelOperation(
      google::cloud::CompletionQueue& cq,
      std::unique_ptr<google::cloud::rest_internal::RestContext> rest_context,
      $longrunning_cancel_operation_request_type$ const& request) override;
)""");
  }

  HeaderPrint(R"""(
 private:
  void SetMetadata(rest_internal::RestContext& rest_context,
                   std::vector<std::string> const& params = {});

  std::shared_ptr<$stub_rest_class_name$> child_;
  std::string api_client_header_;
};
)""");

  HeaderCloseNamespaces();
  HeaderPrint("\n#endif  // $header_include_guard$\n");
  return {};
}

Status MetadataDecoratorRestGenerator::GenerateCc() {
  CcPrint(CopyrightLicenseFileHeader());
  CcPrint(R"""(
// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: $proto_file_name$

)""");

  // includes
  CcPrint("\n");
  CcLocalIncludes({vars("metadata_rest_header_path"),
                   "google/cloud/internal/api_client_header.h",
                   HasExplicitRoutingMethod()
                       ? "google/cloud/internal/routing_matcher.h"
                       : "",
                   "google/cloud/common_options.h", "google/cloud/status_or.h",
                   "google/cloud/internal/absl_str_cat_quiet.h",
                   "google/cloud/internal/absl_str_join_quiet.h",
                   "absl/strings/str_format.h"});
  CcSystemIncludes({"memory"});

  auto result = CcOpenNamespaces(NamespaceType::kInternal);
  if (!result.ok()) return result;

  // constructor
  CcPrint(R"""(
$metadata_rest_class_name$::$metadata_rest_class_name$(
    std::shared_ptr<$stub_rest_class_name$> child)
    : child_(std::move(child)),
      api_client_header_(google::cloud::internal::ApiClientHeader("generator")) {}
)""");

  // metadata decorator class member methods
  for (auto const& method : methods()) {
    if (IsStreaming(method)) continue;
    if (!HasHttpAnnotation(method)) continue;
    if (IsLongrunningOperation(method)) {
      CcPrintMethod(method, __FILE__, __LINE__, R"""(
future<StatusOr<$response_type$>>
$metadata_rest_class_name$::Async$method_name$(
      CompletionQueue& cq,
      std::unique_ptr<rest_internal::RestContext> rest_context,
      $request_type$ const& request) {
)""");
      CcPrintMethod(method, __FILE__, __LINE__,
                    SetMetadataText(method, kPointer));
      CcPrintMethod(method, __FILE__, __LINE__, R"""(
  return child_->Async$method_name$(cq, std::move(rest_context), request);
}
)""");
    } else {
      if (IsResponseTypeEmpty(method)) {
        CcPrintMethod(method, __FILE__, __LINE__, R"""(
Status
$metadata_rest_class_name$::$method_name$(
    rest_internal::RestContext& rest_context,
    $request_type$ const& request) {
)""");
        CcPrintMethod(method, __FILE__, __LINE__,
                      SetMetadataText(method, kReference));
        CcPrintMethod(method, __FILE__, __LINE__, R"""(
  return child_->$method_name$(rest_context, request);
}
)""");
      } else {
        CcPrintMethod(method, __FILE__, __LINE__, R"""(
StatusOr<$response_type$>
$metadata_rest_class_name$::$method_name$(
    rest_internal::RestContext& rest_context,
    $request_type$ const& request) {
)""");
        CcPrintMethod(method, __FILE__, __LINE__,
                      SetMetadataText(method, kReference));
        CcPrintMethod(method, __FILE__, __LINE__, R"""(
  return child_->$method_name$(rest_context, request);
}
)""");
      }
    }
  }

  for (auto const& method : async_methods()) {
    if (IsStreaming(method)) continue;
    if (!HasHttpAnnotation(method)) continue;
    if (IsResponseTypeEmpty(method)) {
      CcPrintMethod(method, __FILE__, __LINE__, R"""(
future<Status>
$metadata_rest_class_name$::Async$method_name$(
      google::cloud::CompletionQueue& cq,
      std::unique_ptr<rest_internal::RestContext> rest_context,
    $request_type$ const& request) {
)""");
      CcPrintMethod(method, __FILE__, __LINE__,
                    SetMetadataText(method, kPointer));
      CcPrintMethod(method, __FILE__, __LINE__, R"""(
  return child_->Async$method_name$(cq, std::move(rest_context), request);
}
)""");
    } else {
      CcPrintMethod(method, __FILE__, __LINE__, R"""(
future<StatusOr<$response_type$>>
$metadata_rest_class_name$::Async$method_name$(
    google::cloud::CompletionQueue& cq,
      std::unique_ptr<rest_internal::RestContext> rest_context,
    $request_type$ const& request) {
)""");
      CcPrintMethod(method, __FILE__, __LINE__,
                    SetMetadataText(method, kPointer));
      CcPrintMethod(method, __FILE__, __LINE__, R"""(
  return child_->Async$method_name$(cq, std::move(rest_context), request);
}
)""");
    }
  }

  if (HasLongrunningMethod()) {
    CcPrint(
        R"""(
future<StatusOr<$longrunning_response_type$>>
$metadata_rest_class_name$::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<rest_internal::RestContext> rest_context,
    $longrunning_get_operation_request_type$ const& request) {
  SetMetadata(*rest_context);
  return child_->AsyncGetOperation(cq, std::move(rest_context), request);
}

future<Status>
$metadata_rest_class_name$::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<rest_internal::RestContext> rest_context,
    $longrunning_cancel_operation_request_type$ const& request) {
  SetMetadata(*rest_context);
  return child_->AsyncCancelOperation(cq, std::move(rest_context), request);
}
)""");
  }

  // The metadata options supported come from
  // https://cloud.google.com/apis/docs/system-parameters.
  // Not all of these system parameters are supported as metadata. Some system
  // parameters are handled by other layers in the REST transport stack.
  CcPrint(R"""(
void $metadata_rest_class_name$::SetMetadata(
      rest_internal::RestContext& rest_context,
      std::vector<std::string> const& params) {
  rest_context.AddHeader("x-goog-api-client", api_client_header_);
  if (!params.empty()) {
    rest_context.AddHeader("x-goog-request-params", absl::StrJoin(params, "&"));
  }
  auto const& options = internal::CurrentOptions();
  if (options.has<UserProjectOption>()) {
    rest_context.AddHeader(
        "x-goog-user-project", options.get<UserProjectOption>());
  }
  if (options.has<google::cloud::QuotaUserOption>()) {
    rest_context.AddHeader(
        "x-goog-quota-user", options.get<google::cloud::QuotaUserOption>());
  }
  if (options.has<google::cloud::ServerTimeoutOption>()) {
    auto ms_rep = absl::StrCat(
        absl::Dec(options.get<google::cloud::ServerTimeoutOption>().count(),
        absl::kZeroPad4));
    rest_context.AddHeader("x-server-timeout",
        ms_rep.insert(ms_rep.size() - 3, "."));
  }
}
)""");

  CcCloseNamespaces();
  return {};
}

}  // namespace generator_internal
}  // namespace cloud
}  // namespace google

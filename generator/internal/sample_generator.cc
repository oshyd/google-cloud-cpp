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

#include "generator/internal/sample_generator.h"

namespace google {
namespace cloud {
namespace generator_internal {

SampleGenerator::SampleGenerator(
    google::protobuf::ServiceDescriptor const* service_descriptor,
    VarsDictionary service_vars,
    std::map<std::string, VarsDictionary> service_method_vars,
    google::protobuf::compiler::GeneratorContext* context)
    : ServiceCodeGenerator("client_samples_cc_path", service_descriptor,
                           std::move(service_vars),
                           std::move(service_method_vars), context) {}

Status SampleGenerator::GenerateCc() { return {}; }

Status SampleGenerator::GenerateHeader() {
  auto endpoint_location_style = EndpointLocationStyle();

  HeaderPrint(CopyrightLicenseFileHeader());
  HeaderPrint(R"""(
// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: $proto_file_name$

)""");

  HeaderLocalIncludes({
      vars("client_header_path"),
      vars("options_header_path"),
      vars("idempotency_policy_header_path"),
      "google/cloud/common_options.h",
      "google/cloud/credentials.h",
      HasLongrunningMethod() ? "google/cloud/polling_policy.h" : "",
      "google/cloud/internal/getenv.h",
      "google/cloud/testing_util/example_driver.h",
      IsExperimental() ? "google/cloud/experimental_tag.h" : "",
  });
  HeaderSystemIncludes({"iostream", "fstream", "string", "vector"});

  HeaderPrint(R"""(
// clang-format off
// main-dox-marker: $product_namespace$::$client_class_name$)""");
  if (HasLongrunningMethod()) {
    HeaderPrint(R"""(
// lro-marker: true)""");
  }
  HeaderPrint(R"""(
// clang-format on
namespace {

void SetClientEndpoint(std::vector<std::string> const& argv) {
  if (!argv.empty()) {
    throw google::cloud::testing_util::Usage{"set-client-endpoint"};
  }
  //! [set-client-endpoint]
  // This configuration is common with Private Google Access:
  //     https://cloud.google.com/vpc/docs/private-google-access
  auto options = google::cloud::Options{}.set<google::cloud::EndpointOption>(
      "private.googleapis.com");
  auto client = google::cloud::$product_namespace$::$client_class_name$()""");
  if (IsExperimental()) HeaderPrint("google::cloud::ExperimentalTag{},");
  if (HasGenerateGrpcTransport()) {
    HeaderPrint(R"""(
      google::cloud::$product_namespace$::Make$connection_class_name$()""");
  } else {
    HeaderPrint(R"""(
      google::cloud::$product_namespace$::Make$connection_class_name$Rest()""");
  }
  if (IsExperimental()) HeaderPrint("google::cloud::ExperimentalTag{},");
  switch (endpoint_location_style) {
    case ServiceConfiguration::LOCATION_DEPENDENT:
      HeaderPrint(R"""("unused", )""");
      break;
    case ServiceConfiguration::LOCATION_DEPENDENT_COMPAT:
    default:
      break;
  }
  HeaderPrint(R"""(options));
  //! [set-client-endpoint]
}

//! [custom-idempotency-policy]
class CustomIdempotencyPolicy
   : public google::cloud::$product_namespace$::$idempotency_class_name$ {
 public:
  ~CustomIdempotencyPolicy() override = default;
  std::unique_ptr<google::cloud::$product_namespace$::$idempotency_class_name$> clone() const override {
    return std::make_unique<CustomIdempotencyPolicy>(*this);
  }
  // Override inherited functions to define as needed.
};
//! [custom-idempotency-policy]

void SetRetryPolicy(std::vector<std::string> const& argv) {
  if (!argv.empty()) {
    throw google::cloud::testing_util::Usage{"set-client-retry-policy"};
  }
  //! [set-retry-policy]
  auto options = google::cloud::Options{}
    .set<google::cloud::$product_namespace$::$idempotency_class_name$Option>(
      CustomIdempotencyPolicy().clone())
    .set<google::cloud::$product_namespace$::$retry_policy_name$Option>(
      google::cloud::$product_namespace$::$limited_error_count_retry_policy_name$(3).clone())
    .set<google::cloud::$product_namespace$::$service_name$BackoffPolicyOption>(
      google::cloud::ExponentialBackoffPolicy(
          /*initial_delay=*/std::chrono::milliseconds(200),
          /*maximum_delay=*/std::chrono::seconds(45),
          /*scaling=*/2.0).clone());)""");
  if (HasGenerateGrpcTransport()) {
    HeaderPrint(R"""(
  auto connection = google::cloud::$product_namespace$::Make$connection_class_name$()""");
  } else {
    HeaderPrint(R"""(
  auto connection = google::cloud::$product_namespace$::Make$connection_class_name$Rest()""");
  }
  if (IsExperimental()) HeaderPrint("google::cloud::ExperimentalTag{}, ");
  switch (endpoint_location_style) {
    case ServiceConfiguration::LOCATION_DEPENDENT:
      HeaderPrint(R"""("location-unused-in-this-example", )""");
      break;
    case ServiceConfiguration::LOCATION_DEPENDENT_COMPAT:
    default:
      break;
  }
  HeaderPrint(R"""(options);)""");
  if (IsExperimental()) {
    HeaderPrint(R"""(

  // c1 and c2 share the same retry policies
  auto c1 = google::cloud::$product_namespace$::$client_class_name$(
    google::cloud::ExperimentalTag{}, connection);
  auto c2 = google::cloud::$product_namespace$::$client_class_name$(
    google::cloud::ExperimentalTag{}, connection);

  // You can override any of the policies in a new client. This new client
  // will share the policies from c1 (or c2) *except* for the retry policy.
  auto c3 = google::cloud::$product_namespace$::$client_class_name$(
    google::cloud::ExperimentalTag{}, connection,
    google::cloud::Options{}.set<google::cloud::$product_namespace$::$retry_policy_name$Option>(
      google::cloud::$product_namespace$::$limited_time_retry_policy_name$(std::chrono::minutes(5)).clone()));

  // You can also override the policies in a single call:
  // c3.SomeRpc(..., google::cloud::Options{}
  //     .set<google::cloud::$product_namespace$::$retry_policy_name$Option>(
  //       google::cloud::$product_namespace$::$limited_error_count_retry_policy_name$(10).clone()));
  //! [set-retry-policy]
}
)""");
  } else
    HeaderPrint(R"""(

  // c1 and c2 share the same retry policies
  auto c1 = google::cloud::$product_namespace$::$client_class_name$(connection);
  auto c2 = google::cloud::$product_namespace$::$client_class_name$(connection);

  // You can override any of the policies in a new client. This new client
  // will share the policies from c1 (or c2) *except* for the retry policy.
  auto c3 = google::cloud::$product_namespace$::$client_class_name$(
    connection, google::cloud::Options{}.set<google::cloud::$product_namespace$::$retry_policy_name$Option>(
      google::cloud::$product_namespace$::$limited_time_retry_policy_name$(std::chrono::minutes(5)).clone()));

  // You can also override the policies in a single call:
  // c3.SomeRpc(..., google::cloud::Options{}
  //     .set<google::cloud::$product_namespace$::$retry_policy_name$Option>(
  //       google::cloud::$product_namespace$::$limited_error_count_retry_policy_name$(10).clone()));
  //! [set-retry-policy]
}
)""");

  if (HasLongrunningMethod()) {
    HeaderPrint(R"""(
void SetPollingPolicy(std::vector<std::string> const& argv) {
  if (!argv.empty()) {
    throw google::cloud::testing_util::Usage{"set-client-policy-policy"};
  }
  //! [set-polling-policy]

  // The polling policy controls how the client waits for long-running
  // operations. `GenericPollingPolicy<>` combines existing policies.
  // In this case, keep polling until the operation completes (with success
  // or error) or 45 minutes, whichever happens first. Initially pause for
  // 10 seconds between polling requests, increasing the pause by a factor
  // of 4 until it becomes 2 minutes.
  auto options = google::cloud::Options{}
    .set<google::cloud::$product_namespace$::$service_name$PollingPolicyOption>(
        google::cloud::GenericPollingPolicy<
            google::cloud::$product_namespace$::$service_name$RetryPolicyOption::Type,
            google::cloud::$product_namespace$::$service_name$BackoffPolicyOption::Type>(
            google::cloud::$product_namespace$::$service_name$LimitedTimeRetryPolicy(
                /*maximum_duration=*/std::chrono::minutes(45))
                .clone(),
            google::cloud::ExponentialBackoffPolicy(
                /*initial_delay=*/std::chrono::seconds(10),
                /*maximum_delay=*/std::chrono::minutes(2),
                /*scaling=*/4.0).clone())
            .clone());
  )""");
    if (HasGenerateGrpcTransport()) {
      HeaderPrint(R"""(
  auto connection = google::cloud::$product_namespace$::Make$connection_class_name$()""");
    } else {
      HeaderPrint(R"""(
  auto connection = google::cloud::$product_namespace$::Make$connection_class_name$Rest()""");
    }
    if (IsExperimental()) HeaderPrint("google::cloud::ExperimentalTag{}, ");
    switch (endpoint_location_style) {
      case ServiceConfiguration::LOCATION_DEPENDENT:
        HeaderPrint(R"""("location-unused-in-this-example", )""");
        break;
      case ServiceConfiguration::LOCATION_DEPENDENT_COMPAT:
      default:
        break;
    }
    HeaderPrint(R"""(options);)""");
    if (IsExperimental()) {
      HeaderPrint(R"""(

  // c1 and c2 share the same polling policies.
  auto c1 = google::cloud::$product_namespace$::$client_class_name$(
    google::cloud::ExperimentalTag{}, connection);
  auto c2 = google::cloud::$product_namespace$::$client_class_name$(
    google::cloud::ExperimentalTag{}, connection);
  //! [set-polling-policy]
}
)""");
    } else
      HeaderPrint(R"""(

  // c1 and c2 share the same polling policies.
  auto c1 = google::cloud::$product_namespace$::$client_class_name$(connection);
  auto c2 = google::cloud::$product_namespace$::$client_class_name$(connection);
  //! [set-polling-policy]
}
)""");
  }
  HeaderPrint(R"""(
void WithServiceAccount(std::vector<std::string> const& argv) {
  if (argv.size() != 1 || argv[0] == "--help") {
    throw google::cloud::testing_util::Usage{"with-service-account <keyfile>"};
  }
  //! [with-service-account]
  [](std::string const& keyfile) {
    auto is = std::ifstream(keyfile);
    is.exceptions(std::ios::badbit);  // Minimal error handling in examples
    auto contents = std::string(std::istreambuf_iterator<char>(is.rdbuf()), {});
    auto options =
        google::cloud::Options{}.set<google::cloud::UnifiedCredentialsOption>(
            google::cloud::MakeServiceAccountCredentials(contents));
    return google::cloud::$product_namespace$::$client_class_name$()""");
  if (IsExperimental()) HeaderPrint("google::cloud::ExperimentalTag{},");
  if (HasGenerateGrpcTransport()) {
    HeaderPrint(R"""(
      google::cloud::$product_namespace$::Make$connection_class_name$()""");
  } else {
    HeaderPrint(R"""(
      google::cloud::$product_namespace$::Make$connection_class_name$Rest()""");
  }
  if (IsExperimental()) HeaderPrint("google::cloud::ExperimentalTag{},");
  switch (endpoint_location_style) {
    case ServiceConfiguration::LOCATION_DEPENDENT:
      HeaderPrint(R"""("us-west1" /* regional service region */, )""");
      break;
    case ServiceConfiguration::LOCATION_DEPENDENT_COMPAT:
    default:
      break;
  }
  HeaderPrint(R"""(options));
  }
  //! [with-service-account]
  (argv.at(0));
}

void AutoRun(std::vector<std::string> const& argv) {
  namespace examples = ::google::cloud::testing_util;
  using ::google::cloud::internal::GetEnv;
  if (!argv.empty()) throw examples::Usage{"auto"};
  examples::CheckEnvironmentVariablesAreSet({
    "GOOGLE_CLOUD_CPP_TEST_SERVICE_ACCOUNT_KEYFILE"
  });
  auto const keyfile =
      GetEnv("GOOGLE_CLOUD_CPP_TEST_SERVICE_ACCOUNT_KEYFILE").value();

  std::cout << "\nRunning SetClientEndpoint() example" << std::endl;
  SetClientEndpoint({});

  std::cout << "\nRunning SetRetryPolicy() example" << std::endl;
  SetRetryPolicy({});
 )""");
  if (HasLongrunningMethod()) {
    HeaderPrint(R"""(
  std::cout << "\nRunning SetPollingPolicy() example" << std::endl;
  SetPollingPolicy({});
)""");
  }
  HeaderPrint(R"""(
  std::cout << "\nRunning WithServiceAccount() example" << std::endl;
  WithServiceAccount({keyfile});
}

}  // namespace

int main(int argc, char* argv[]) {  // NOLINT(bugprone-exception-escape)
  google::cloud::testing_util::Example example({
      {"set-client-endpoint", SetClientEndpoint},
      {"set-retry-policy", SetRetryPolicy},
  )""");
  if (HasLongrunningMethod()) {
    HeaderPrint(R"""(      {"set-polling-policy", SetPollingPolicy},
    )""");
  }
  HeaderPrint(R"""(      {"with-service-account", WithServiceAccount},
      {"auto", AutoRun},
  });
  return example.Run(argc, argv);
}
)""");

  return {};
}

}  // namespace generator_internal
}  // namespace cloud
}  // namespace google

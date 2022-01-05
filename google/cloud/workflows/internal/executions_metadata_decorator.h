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

// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: google/cloud/workflows/executions/v1/executions.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_WORKFLOWS_INTERNAL_EXECUTIONS_METADATA_DECORATOR_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_WORKFLOWS_INTERNAL_EXECUTIONS_METADATA_DECORATOR_H

#include "google/cloud/workflows/internal/executions_stub.h"
#include "google/cloud/version.h"
#include <memory>
#include <string>

namespace google {
namespace cloud {
namespace workflows_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class ExecutionsMetadata : public ExecutionsStub {
 public:
  ~ExecutionsMetadata() override = default;
  explicit ExecutionsMetadata(std::shared_ptr<ExecutionsStub> child);

  StatusOr<google::cloud::workflows::executions::v1::ListExecutionsResponse>
  ListExecutions(
      grpc::ClientContext& context,
      google::cloud::workflows::executions::v1::ListExecutionsRequest const&
          request) override;

  StatusOr<google::cloud::workflows::executions::v1::Execution> CreateExecution(
      grpc::ClientContext& context,
      google::cloud::workflows::executions::v1::CreateExecutionRequest const&
          request) override;

  StatusOr<google::cloud::workflows::executions::v1::Execution> GetExecution(
      grpc::ClientContext& context,
      google::cloud::workflows::executions::v1::GetExecutionRequest const&
          request) override;

  StatusOr<google::cloud::workflows::executions::v1::Execution> CancelExecution(
      grpc::ClientContext& context,
      google::cloud::workflows::executions::v1::CancelExecutionRequest const&
          request) override;

 private:
  void SetMetadata(grpc::ClientContext& context,
                   std::string const& request_params);
  std::shared_ptr<ExecutionsStub> child_;
  std::string api_client_header_;
};  // ExecutionsMetadata

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace workflows_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_WORKFLOWS_INTERNAL_EXECUTIONS_METADATA_DECORATOR_H

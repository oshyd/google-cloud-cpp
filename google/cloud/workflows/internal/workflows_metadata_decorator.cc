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
// source: google/cloud/workflows/v1/workflows.proto

#include "google/cloud/workflows/internal/workflows_metadata_decorator.h"
#include "google/cloud/internal/api_client_header.h"
#include "google/cloud/status_or.h"
#include <google/cloud/workflows/v1/workflows.grpc.pb.h>
#include <memory>

namespace google {
namespace cloud {
namespace workflows_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

WorkflowsMetadata::WorkflowsMetadata(std::shared_ptr<WorkflowsStub> child)
    : child_(std::move(child)),
      api_client_header_(
          google::cloud::internal::ApiClientHeader("generator")) {}

StatusOr<google::cloud::workflows::v1::ListWorkflowsResponse>
WorkflowsMetadata::ListWorkflows(
    grpc::ClientContext& context,
    google::cloud::workflows::v1::ListWorkflowsRequest const& request) {
  SetMetadata(context, "parent=" + request.parent());
  return child_->ListWorkflows(context, request);
}

StatusOr<google::cloud::workflows::v1::Workflow> WorkflowsMetadata::GetWorkflow(
    grpc::ClientContext& context,
    google::cloud::workflows::v1::GetWorkflowRequest const& request) {
  SetMetadata(context, "name=" + request.name());
  return child_->GetWorkflow(context, request);
}

future<StatusOr<google::longrunning::Operation>>
WorkflowsMetadata::AsyncCreateWorkflow(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::cloud::workflows::v1::CreateWorkflowRequest const& request) {
  SetMetadata(*context, "parent=" + request.parent());
  return child_->AsyncCreateWorkflow(cq, std::move(context), request);
}

future<StatusOr<google::longrunning::Operation>>
WorkflowsMetadata::AsyncDeleteWorkflow(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::cloud::workflows::v1::DeleteWorkflowRequest const& request) {
  SetMetadata(*context, "name=" + request.name());
  return child_->AsyncDeleteWorkflow(cq, std::move(context), request);
}

future<StatusOr<google::longrunning::Operation>>
WorkflowsMetadata::AsyncUpdateWorkflow(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::cloud::workflows::v1::UpdateWorkflowRequest const& request) {
  SetMetadata(*context, "workflow.name=" + request.workflow().name());
  return child_->AsyncUpdateWorkflow(cq, std::move(context), request);
}

future<StatusOr<google::longrunning::Operation>>
WorkflowsMetadata::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::longrunning::GetOperationRequest const& request) {
  SetMetadata(*context, "name=" + request.name());
  return child_->AsyncGetOperation(cq, std::move(context), request);
}

future<Status> WorkflowsMetadata::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::unique_ptr<grpc::ClientContext> context,
    google::longrunning::CancelOperationRequest const& request) {
  SetMetadata(*context, "name=" + request.name());
  return child_->AsyncCancelOperation(cq, std::move(context), request);
}

void WorkflowsMetadata::SetMetadata(grpc::ClientContext& context,
                                    std::string const& request_params) {
  context.AddMetadata("x-goog-request-params", request_params);
  context.AddMetadata("x-goog-api-client", api_client_header_);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace workflows_internal
}  // namespace cloud
}  // namespace google

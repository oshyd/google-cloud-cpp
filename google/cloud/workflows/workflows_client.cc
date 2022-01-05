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

#include "google/cloud/workflows/workflows_client.h"
#include "google/cloud/workflows/internal/workflows_option_defaults.h"
#include <memory>

namespace google {
namespace cloud {
namespace workflows {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

WorkflowsClient::WorkflowsClient(
    std::shared_ptr<WorkflowsConnection> connection, Options options)
    : connection_(std::move(connection)),
      options_(
          workflows_internal::WorkflowsDefaultOptions(std::move(options))) {}
WorkflowsClient::~WorkflowsClient() = default;

StreamRange<google::cloud::workflows::v1::Workflow>
WorkflowsClient::ListWorkflows(std::string const& parent, Options options) {
  internal::OptionsSpan span(
      internal::MergeOptions(std::move(options), options_));
  google::cloud::workflows::v1::ListWorkflowsRequest request;
  request.set_parent(parent);
  return connection_->ListWorkflows(request);
}

StreamRange<google::cloud::workflows::v1::Workflow>
WorkflowsClient::ListWorkflows(
    google::cloud::workflows::v1::ListWorkflowsRequest request,
    Options options) {
  internal::OptionsSpan span(
      internal::MergeOptions(std::move(options), options_));
  return connection_->ListWorkflows(std::move(request));
}

StatusOr<google::cloud::workflows::v1::Workflow> WorkflowsClient::GetWorkflow(
    std::string const& name, Options options) {
  internal::OptionsSpan span(
      internal::MergeOptions(std::move(options), options_));
  google::cloud::workflows::v1::GetWorkflowRequest request;
  request.set_name(name);
  return connection_->GetWorkflow(request);
}

StatusOr<google::cloud::workflows::v1::Workflow> WorkflowsClient::GetWorkflow(
    google::cloud::workflows::v1::GetWorkflowRequest const& request,
    Options options) {
  internal::OptionsSpan span(
      internal::MergeOptions(std::move(options), options_));
  return connection_->GetWorkflow(request);
}

future<StatusOr<google::cloud::workflows::v1::Workflow>>
WorkflowsClient::CreateWorkflow(
    std::string const& parent,
    google::cloud::workflows::v1::Workflow const& workflow,
    std::string const& workflow_id, Options options) {
  internal::OptionsSpan span(
      internal::MergeOptions(std::move(options), options_));
  google::cloud::workflows::v1::CreateWorkflowRequest request;
  request.set_parent(parent);
  *request.mutable_workflow() = workflow;
  request.set_workflow_id(workflow_id);
  return connection_->CreateWorkflow(request);
}

future<StatusOr<google::cloud::workflows::v1::Workflow>>
WorkflowsClient::CreateWorkflow(
    google::cloud::workflows::v1::CreateWorkflowRequest const& request,
    Options options) {
  internal::OptionsSpan span(
      internal::MergeOptions(std::move(options), options_));
  return connection_->CreateWorkflow(request);
}

future<StatusOr<google::cloud::workflows::v1::OperationMetadata>>
WorkflowsClient::DeleteWorkflow(std::string const& name, Options options) {
  internal::OptionsSpan span(
      internal::MergeOptions(std::move(options), options_));
  google::cloud::workflows::v1::DeleteWorkflowRequest request;
  request.set_name(name);
  return connection_->DeleteWorkflow(request);
}

future<StatusOr<google::cloud::workflows::v1::OperationMetadata>>
WorkflowsClient::DeleteWorkflow(
    google::cloud::workflows::v1::DeleteWorkflowRequest const& request,
    Options options) {
  internal::OptionsSpan span(
      internal::MergeOptions(std::move(options), options_));
  return connection_->DeleteWorkflow(request);
}

future<StatusOr<google::cloud::workflows::v1::Workflow>>
WorkflowsClient::UpdateWorkflow(
    google::cloud::workflows::v1::Workflow const& workflow,
    google::protobuf::FieldMask const& update_mask, Options options) {
  internal::OptionsSpan span(
      internal::MergeOptions(std::move(options), options_));
  google::cloud::workflows::v1::UpdateWorkflowRequest request;
  *request.mutable_workflow() = workflow;
  *request.mutable_update_mask() = update_mask;
  return connection_->UpdateWorkflow(request);
}

future<StatusOr<google::cloud::workflows::v1::Workflow>>
WorkflowsClient::UpdateWorkflow(
    google::cloud::workflows::v1::UpdateWorkflowRequest const& request,
    Options options) {
  internal::OptionsSpan span(
      internal::MergeOptions(std::move(options), options_));
  return connection_->UpdateWorkflow(request);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace workflows
}  // namespace cloud
}  // namespace google

// Copyright 2024 Google LLC
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
// source: google/cloud/securitycenter/v2/securitycenter_service.proto

#include "google/cloud/securitycenter/v2/internal/security_center_stub.h"
#include "google/cloud/grpc_error_delegate.h"
#include "google/cloud/status_or.h"
#include <google/cloud/securitycenter/v2/securitycenter_service.grpc.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace securitycenter_v2_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

SecurityCenterStub::~SecurityCenterStub() = default;

StatusOr<
    google::cloud::securitycenter::v2::BatchCreateResourceValueConfigsResponse>
DefaultSecurityCenterStub::BatchCreateResourceValueConfigs(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::
        BatchCreateResourceValueConfigsRequest const& request) {
  google::cloud::securitycenter::v2::BatchCreateResourceValueConfigsResponse
      response;
  auto status =
      grpc_stub_->BatchCreateResourceValueConfigs(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

future<StatusOr<google::longrunning::Operation>>
DefaultSecurityCenterStub::AsyncBulkMuteFindings(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    google::cloud::internal::ImmutableOptions,
    google::cloud::securitycenter::v2::BulkMuteFindingsRequest const& request) {
  return internal::MakeUnaryRpcImpl<
      google::cloud::securitycenter::v2::BulkMuteFindingsRequest,
      google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::cloud::securitycenter::v2::BulkMuteFindingsRequest const&
                 request,
             grpc::CompletionQueue* cq) {
        return grpc_stub_->AsyncBulkMuteFindings(context, request, cq);
      },
      request, std::move(context));
}

StatusOr<google::longrunning::Operation>
DefaultSecurityCenterStub::BulkMuteFindings(
    grpc::ClientContext& context, Options,
    google::cloud::securitycenter::v2::BulkMuteFindingsRequest const& request) {
  google::longrunning::Operation response;
  auto status = grpc_stub_->BulkMuteFindings(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::BigQueryExport>
DefaultSecurityCenterStub::CreateBigQueryExport(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::CreateBigQueryExportRequest const&
        request) {
  google::cloud::securitycenter::v2::BigQueryExport response;
  auto status = grpc_stub_->CreateBigQueryExport(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::Finding>
DefaultSecurityCenterStub::CreateFinding(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::CreateFindingRequest const& request) {
  google::cloud::securitycenter::v2::Finding response;
  auto status = grpc_stub_->CreateFinding(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::MuteConfig>
DefaultSecurityCenterStub::CreateMuteConfig(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::CreateMuteConfigRequest const& request) {
  google::cloud::securitycenter::v2::MuteConfig response;
  auto status = grpc_stub_->CreateMuteConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::NotificationConfig>
DefaultSecurityCenterStub::CreateNotificationConfig(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::CreateNotificationConfigRequest const&
        request) {
  google::cloud::securitycenter::v2::NotificationConfig response;
  auto status =
      grpc_stub_->CreateNotificationConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::Source>
DefaultSecurityCenterStub::CreateSource(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::CreateSourceRequest const& request) {
  google::cloud::securitycenter::v2::Source response;
  auto status = grpc_stub_->CreateSource(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

Status DefaultSecurityCenterStub::DeleteBigQueryExport(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::DeleteBigQueryExportRequest const&
        request) {
  google::protobuf::Empty response;
  auto status = grpc_stub_->DeleteBigQueryExport(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

Status DefaultSecurityCenterStub::DeleteMuteConfig(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::DeleteMuteConfigRequest const& request) {
  google::protobuf::Empty response;
  auto status = grpc_stub_->DeleteMuteConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

Status DefaultSecurityCenterStub::DeleteNotificationConfig(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::DeleteNotificationConfigRequest const&
        request) {
  google::protobuf::Empty response;
  auto status =
      grpc_stub_->DeleteNotificationConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

Status DefaultSecurityCenterStub::DeleteResourceValueConfig(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::DeleteResourceValueConfigRequest const&
        request) {
  google::protobuf::Empty response;
  auto status =
      grpc_stub_->DeleteResourceValueConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

StatusOr<google::cloud::securitycenter::v2::BigQueryExport>
DefaultSecurityCenterStub::GetBigQueryExport(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::GetBigQueryExportRequest const&
        request) {
  google::cloud::securitycenter::v2::BigQueryExport response;
  auto status = grpc_stub_->GetBigQueryExport(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::Simulation>
DefaultSecurityCenterStub::GetSimulation(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::GetSimulationRequest const& request) {
  google::cloud::securitycenter::v2::Simulation response;
  auto status = grpc_stub_->GetSimulation(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ValuedResource>
DefaultSecurityCenterStub::GetValuedResource(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::GetValuedResourceRequest const&
        request) {
  google::cloud::securitycenter::v2::ValuedResource response;
  auto status = grpc_stub_->GetValuedResource(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::iam::v1::Policy> DefaultSecurityCenterStub::GetIamPolicy(
    grpc::ClientContext& context, Options const&,
    google::iam::v1::GetIamPolicyRequest const& request) {
  google::iam::v1::Policy response;
  auto status = grpc_stub_->GetIamPolicy(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::MuteConfig>
DefaultSecurityCenterStub::GetMuteConfig(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::GetMuteConfigRequest const& request) {
  google::cloud::securitycenter::v2::MuteConfig response;
  auto status = grpc_stub_->GetMuteConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::NotificationConfig>
DefaultSecurityCenterStub::GetNotificationConfig(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::GetNotificationConfigRequest const&
        request) {
  google::cloud::securitycenter::v2::NotificationConfig response;
  auto status = grpc_stub_->GetNotificationConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ResourceValueConfig>
DefaultSecurityCenterStub::GetResourceValueConfig(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::GetResourceValueConfigRequest const&
        request) {
  google::cloud::securitycenter::v2::ResourceValueConfig response;
  auto status =
      grpc_stub_->GetResourceValueConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::Source>
DefaultSecurityCenterStub::GetSource(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::GetSourceRequest const& request) {
  google::cloud::securitycenter::v2::Source response;
  auto status = grpc_stub_->GetSource(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::GroupFindingsResponse>
DefaultSecurityCenterStub::GroupFindings(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::GroupFindingsRequest const& request) {
  google::cloud::securitycenter::v2::GroupFindingsResponse response;
  auto status = grpc_stub_->GroupFindings(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ListAttackPathsResponse>
DefaultSecurityCenterStub::ListAttackPaths(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::ListAttackPathsRequest const& request) {
  google::cloud::securitycenter::v2::ListAttackPathsResponse response;
  auto status = grpc_stub_->ListAttackPaths(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ListBigQueryExportsResponse>
DefaultSecurityCenterStub::ListBigQueryExports(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::ListBigQueryExportsRequest const&
        request) {
  google::cloud::securitycenter::v2::ListBigQueryExportsResponse response;
  auto status = grpc_stub_->ListBigQueryExports(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ListFindingsResponse>
DefaultSecurityCenterStub::ListFindings(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::ListFindingsRequest const& request) {
  google::cloud::securitycenter::v2::ListFindingsResponse response;
  auto status = grpc_stub_->ListFindings(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ListMuteConfigsResponse>
DefaultSecurityCenterStub::ListMuteConfigs(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::ListMuteConfigsRequest const& request) {
  google::cloud::securitycenter::v2::ListMuteConfigsResponse response;
  auto status = grpc_stub_->ListMuteConfigs(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ListNotificationConfigsResponse>
DefaultSecurityCenterStub::ListNotificationConfigs(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::ListNotificationConfigsRequest const&
        request) {
  google::cloud::securitycenter::v2::ListNotificationConfigsResponse response;
  auto status =
      grpc_stub_->ListNotificationConfigs(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ListResourceValueConfigsResponse>
DefaultSecurityCenterStub::ListResourceValueConfigs(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::ListResourceValueConfigsRequest const&
        request) {
  google::cloud::securitycenter::v2::ListResourceValueConfigsResponse response;
  auto status =
      grpc_stub_->ListResourceValueConfigs(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ListSourcesResponse>
DefaultSecurityCenterStub::ListSources(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::ListSourcesRequest const& request) {
  google::cloud::securitycenter::v2::ListSourcesResponse response;
  auto status = grpc_stub_->ListSources(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ListValuedResourcesResponse>
DefaultSecurityCenterStub::ListValuedResources(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::ListValuedResourcesRequest const&
        request) {
  google::cloud::securitycenter::v2::ListValuedResourcesResponse response;
  auto status = grpc_stub_->ListValuedResources(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::Finding>
DefaultSecurityCenterStub::SetFindingState(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::SetFindingStateRequest const& request) {
  google::cloud::securitycenter::v2::Finding response;
  auto status = grpc_stub_->SetFindingState(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::iam::v1::Policy> DefaultSecurityCenterStub::SetIamPolicy(
    grpc::ClientContext& context, Options const&,
    google::iam::v1::SetIamPolicyRequest const& request) {
  google::iam::v1::Policy response;
  auto status = grpc_stub_->SetIamPolicy(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::Finding>
DefaultSecurityCenterStub::SetMute(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::SetMuteRequest const& request) {
  google::cloud::securitycenter::v2::Finding response;
  auto status = grpc_stub_->SetMute(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::iam::v1::TestIamPermissionsResponse>
DefaultSecurityCenterStub::TestIamPermissions(
    grpc::ClientContext& context, Options const&,
    google::iam::v1::TestIamPermissionsRequest const& request) {
  google::iam::v1::TestIamPermissionsResponse response;
  auto status = grpc_stub_->TestIamPermissions(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::BigQueryExport>
DefaultSecurityCenterStub::UpdateBigQueryExport(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::UpdateBigQueryExportRequest const&
        request) {
  google::cloud::securitycenter::v2::BigQueryExport response;
  auto status = grpc_stub_->UpdateBigQueryExport(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ExternalSystem>
DefaultSecurityCenterStub::UpdateExternalSystem(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::UpdateExternalSystemRequest const&
        request) {
  google::cloud::securitycenter::v2::ExternalSystem response;
  auto status = grpc_stub_->UpdateExternalSystem(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::Finding>
DefaultSecurityCenterStub::UpdateFinding(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::UpdateFindingRequest const& request) {
  google::cloud::securitycenter::v2::Finding response;
  auto status = grpc_stub_->UpdateFinding(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::MuteConfig>
DefaultSecurityCenterStub::UpdateMuteConfig(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::UpdateMuteConfigRequest const& request) {
  google::cloud::securitycenter::v2::MuteConfig response;
  auto status = grpc_stub_->UpdateMuteConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::NotificationConfig>
DefaultSecurityCenterStub::UpdateNotificationConfig(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::UpdateNotificationConfigRequest const&
        request) {
  google::cloud::securitycenter::v2::NotificationConfig response;
  auto status =
      grpc_stub_->UpdateNotificationConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::ResourceValueConfig>
DefaultSecurityCenterStub::UpdateResourceValueConfig(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::UpdateResourceValueConfigRequest const&
        request) {
  google::cloud::securitycenter::v2::ResourceValueConfig response;
  auto status =
      grpc_stub_->UpdateResourceValueConfig(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::SecurityMarks>
DefaultSecurityCenterStub::UpdateSecurityMarks(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::UpdateSecurityMarksRequest const&
        request) {
  google::cloud::securitycenter::v2::SecurityMarks response;
  auto status = grpc_stub_->UpdateSecurityMarks(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::cloud::securitycenter::v2::Source>
DefaultSecurityCenterStub::UpdateSource(
    grpc::ClientContext& context, Options const&,
    google::cloud::securitycenter::v2::UpdateSourceRequest const& request) {
  google::cloud::securitycenter::v2::Source response;
  auto status = grpc_stub_->UpdateSource(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::longrunning::ListOperationsResponse>
DefaultSecurityCenterStub::ListOperations(
    grpc::ClientContext& context, Options const&,
    google::longrunning::ListOperationsRequest const& request) {
  google::longrunning::ListOperationsResponse response;
  auto status = operations_stub_->ListOperations(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

StatusOr<google::longrunning::Operation>
DefaultSecurityCenterStub::GetOperation(
    grpc::ClientContext& context, Options const&,
    google::longrunning::GetOperationRequest const& request) {
  google::longrunning::Operation response;
  auto status = operations_stub_->GetOperation(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return response;
}

Status DefaultSecurityCenterStub::DeleteOperation(
    grpc::ClientContext& context, Options const&,
    google::longrunning::DeleteOperationRequest const& request) {
  google::protobuf::Empty response;
  auto status = operations_stub_->DeleteOperation(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

Status DefaultSecurityCenterStub::CancelOperation(
    grpc::ClientContext& context, Options const&,
    google::longrunning::CancelOperationRequest const& request) {
  google::protobuf::Empty response;
  auto status = operations_stub_->CancelOperation(&context, request, &response);
  if (!status.ok()) {
    return google::cloud::MakeStatusFromRpcError(status);
  }
  return google::cloud::Status();
}

future<StatusOr<google::longrunning::Operation>>
DefaultSecurityCenterStub::AsyncGetOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    google::cloud::internal::ImmutableOptions,
    google::longrunning::GetOperationRequest const& request) {
  return internal::MakeUnaryRpcImpl<google::longrunning::GetOperationRequest,
                                    google::longrunning::Operation>(
      cq,
      [this](grpc::ClientContext* context,
             google::longrunning::GetOperationRequest const& request,
             grpc::CompletionQueue* cq) {
        return operations_stub_->AsyncGetOperation(context, request, cq);
      },
      request, std::move(context));
}

future<Status> DefaultSecurityCenterStub::AsyncCancelOperation(
    google::cloud::CompletionQueue& cq,
    std::shared_ptr<grpc::ClientContext> context,
    // NOLINTNEXTLINE(performance-unnecessary-value-param)
    google::cloud::internal::ImmutableOptions,
    google::longrunning::CancelOperationRequest const& request) {
  return internal::MakeUnaryRpcImpl<google::longrunning::CancelOperationRequest,
                                    google::protobuf::Empty>(
             cq,
             [this](grpc::ClientContext* context,
                    google::longrunning::CancelOperationRequest const& request,
                    grpc::CompletionQueue* cq) {
               return operations_stub_->AsyncCancelOperation(context, request,
                                                             cq);
             },
             request, std::move(context))
      .then([](future<StatusOr<google::protobuf::Empty>> f) {
        return f.get().status();
      });
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace securitycenter_v2_internal
}  // namespace cloud
}  // namespace google

// Copyright 2021 Google LLC
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
// source: google/bigtable/admin/v2/bigtable_table_admin.proto

#include "google/cloud/bigtable/admin/internal/bigtable_table_admin_connection_impl.h"
#include "google/cloud/bigtable/admin/internal/bigtable_table_admin_option_defaults.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/common_options.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/async_long_running_operation.h"
#include "google/cloud/internal/async_retry_loop.h"
#include "google/cloud/internal/pagination_range.h"
#include "google/cloud/internal/retry_loop.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace bigtable_admin_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

std::unique_ptr<bigtable_admin::BigtableTableAdminRetryPolicy> retry_policy(
    Options const& options) {
  return options.get<bigtable_admin::BigtableTableAdminRetryPolicyOption>()
      ->clone();
}

std::unique_ptr<BackoffPolicy> backoff_policy(Options const& options) {
  return options.get<bigtable_admin::BigtableTableAdminBackoffPolicyOption>()
      ->clone();
}

std::unique_ptr<bigtable_admin::BigtableTableAdminConnectionIdempotencyPolicy>
idempotency_policy(Options const& options) {
  return options
      .get<
          bigtable_admin::BigtableTableAdminConnectionIdempotencyPolicyOption>()
      ->clone();
}

std::unique_ptr<PollingPolicy> polling_policy(Options const& options) {
  return options.get<bigtable_admin::BigtableTableAdminPollingPolicyOption>()
      ->clone();
}

}  // namespace

BigtableTableAdminConnectionImpl::BigtableTableAdminConnectionImpl(
    std::unique_ptr<google::cloud::BackgroundThreads> background,
    std::shared_ptr<bigtable_admin_internal::BigtableTableAdminStub> stub,
    Options options)
    : background_(std::move(background)),
      stub_(std::move(stub)),
      options_(internal::MergeOptions(
          std::move(options), BigtableTableAdminConnection::options())) {}

StatusOr<google::bigtable::admin::v2::Table>
BigtableTableAdminConnectionImpl::CreateTable(
    google::bigtable::admin::v2::CreateTableRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->CreateTable(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::bigtable::admin::v2::CreateTableRequest const& request) {
        return stub_->CreateTable(context, options, request);
      },
      *current, request, __func__);
}

StreamRange<google::bigtable::admin::v2::Table>
BigtableTableAdminConnectionImpl::ListTables(
    google::bigtable::admin::v2::ListTablesRequest request) {
  request.clear_page_token();
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto idempotency = idempotency_policy(*current)->ListTables(request);
  char const* function_name = __func__;
  return google::cloud::internal::MakePaginationRange<
      StreamRange<google::bigtable::admin::v2::Table>>(
      current, std::move(request),
      [idempotency, function_name, stub = stub_,
       retry = std::shared_ptr<bigtable_admin::BigtableTableAdminRetryPolicy>(
           retry_policy(*current)),
       backoff = std::shared_ptr<BackoffPolicy>(backoff_policy(*current))](
          Options const& options,
          google::bigtable::admin::v2::ListTablesRequest const& r) {
        return google::cloud::internal::RetryLoop(
            retry->clone(), backoff->clone(), idempotency,
            [stub](
                grpc::ClientContext& context, Options const& options,
                google::bigtable::admin::v2::ListTablesRequest const& request) {
              return stub->ListTables(context, options, request);
            },
            options, r, function_name);
      },
      [](google::bigtable::admin::v2::ListTablesResponse r) {
        std::vector<google::bigtable::admin::v2::Table> result(
            r.tables().size());
        auto& messages = *r.mutable_tables();
        std::move(messages.begin(), messages.end(), result.begin());
        return result;
      });
}

StatusOr<google::bigtable::admin::v2::Table>
BigtableTableAdminConnectionImpl::GetTable(
    google::bigtable::admin::v2::GetTableRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetTable(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::bigtable::admin::v2::GetTableRequest const& request) {
        return stub_->GetTable(context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::bigtable::admin::v2::Table>>
BigtableTableAdminConnectionImpl::UpdateTable(
    google::bigtable::admin::v2::UpdateTableRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto request_copy = request;
  auto const idempotent =
      idempotency_policy(*current)->UpdateTable(request_copy);
  return google::cloud::internal::AsyncLongRunningOperation<
      google::bigtable::admin::v2::Table>(
      background_->cq(), current, std::move(request_copy),
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::bigtable::admin::v2::UpdateTableRequest const& request) {
        return stub->AsyncUpdateTable(cq, std::move(context),
                                      std::move(options), request);
      },
      [stub = stub_](google::cloud::CompletionQueue& cq,
                     std::shared_ptr<grpc::ClientContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::bigtable::admin::v2::Table>,
      retry_policy(*current), backoff_policy(*current), idempotent,
      polling_policy(*current), __func__);
}

Status BigtableTableAdminConnectionImpl::DeleteTable(
    google::bigtable::admin::v2::DeleteTableRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->DeleteTable(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::bigtable::admin::v2::DeleteTableRequest const& request) {
        return stub_->DeleteTable(context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::bigtable::admin::v2::Table>>
BigtableTableAdminConnectionImpl::UndeleteTable(
    google::bigtable::admin::v2::UndeleteTableRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto request_copy = request;
  auto const idempotent =
      idempotency_policy(*current)->UndeleteTable(request_copy);
  return google::cloud::internal::AsyncLongRunningOperation<
      google::bigtable::admin::v2::Table>(
      background_->cq(), current, std::move(request_copy),
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::bigtable::admin::v2::UndeleteTableRequest const& request) {
        return stub->AsyncUndeleteTable(cq, std::move(context),
                                        std::move(options), request);
      },
      [stub = stub_](google::cloud::CompletionQueue& cq,
                     std::shared_ptr<grpc::ClientContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::bigtable::admin::v2::Table>,
      retry_policy(*current), backoff_policy(*current), idempotent,
      polling_policy(*current), __func__);
}

future<StatusOr<google::bigtable::admin::v2::AuthorizedView>>
BigtableTableAdminConnectionImpl::CreateAuthorizedView(
    google::bigtable::admin::v2::CreateAuthorizedViewRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto request_copy = request;
  auto const idempotent =
      idempotency_policy(*current)->CreateAuthorizedView(request_copy);
  return google::cloud::internal::AsyncLongRunningOperation<
      google::bigtable::admin::v2::AuthorizedView>(
      background_->cq(), current, std::move(request_copy),
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::bigtable::admin::v2::CreateAuthorizedViewRequest const&
              request) {
        return stub->AsyncCreateAuthorizedView(cq, std::move(context),
                                               std::move(options), request);
      },
      [stub = stub_](google::cloud::CompletionQueue& cq,
                     std::shared_ptr<grpc::ClientContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::bigtable::admin::v2::AuthorizedView>,
      retry_policy(*current), backoff_policy(*current), idempotent,
      polling_policy(*current), __func__);
}

StreamRange<google::bigtable::admin::v2::AuthorizedView>
BigtableTableAdminConnectionImpl::ListAuthorizedViews(
    google::bigtable::admin::v2::ListAuthorizedViewsRequest request) {
  request.clear_page_token();
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto idempotency = idempotency_policy(*current)->ListAuthorizedViews(request);
  char const* function_name = __func__;
  return google::cloud::internal::MakePaginationRange<
      StreamRange<google::bigtable::admin::v2::AuthorizedView>>(
      current, std::move(request),
      [idempotency, function_name, stub = stub_,
       retry = std::shared_ptr<bigtable_admin::BigtableTableAdminRetryPolicy>(
           retry_policy(*current)),
       backoff = std::shared_ptr<BackoffPolicy>(backoff_policy(*current))](
          Options const& options,
          google::bigtable::admin::v2::ListAuthorizedViewsRequest const& r) {
        return google::cloud::internal::RetryLoop(
            retry->clone(), backoff->clone(), idempotency,
            [stub](
                grpc::ClientContext& context, Options const& options,
                google::bigtable::admin::v2::ListAuthorizedViewsRequest const&
                    request) {
              return stub->ListAuthorizedViews(context, options, request);
            },
            options, r, function_name);
      },
      [](google::bigtable::admin::v2::ListAuthorizedViewsResponse r) {
        std::vector<google::bigtable::admin::v2::AuthorizedView> result(
            r.authorized_views().size());
        auto& messages = *r.mutable_authorized_views();
        std::move(messages.begin(), messages.end(), result.begin());
        return result;
      });
}

StatusOr<google::bigtable::admin::v2::AuthorizedView>
BigtableTableAdminConnectionImpl::GetAuthorizedView(
    google::bigtable::admin::v2::GetAuthorizedViewRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetAuthorizedView(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::bigtable::admin::v2::GetAuthorizedViewRequest const&
                 request) {
        return stub_->GetAuthorizedView(context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::bigtable::admin::v2::AuthorizedView>>
BigtableTableAdminConnectionImpl::UpdateAuthorizedView(
    google::bigtable::admin::v2::UpdateAuthorizedViewRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto request_copy = request;
  auto const idempotent =
      idempotency_policy(*current)->UpdateAuthorizedView(request_copy);
  return google::cloud::internal::AsyncLongRunningOperation<
      google::bigtable::admin::v2::AuthorizedView>(
      background_->cq(), current, std::move(request_copy),
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::bigtable::admin::v2::UpdateAuthorizedViewRequest const&
              request) {
        return stub->AsyncUpdateAuthorizedView(cq, std::move(context),
                                               std::move(options), request);
      },
      [stub = stub_](google::cloud::CompletionQueue& cq,
                     std::shared_ptr<grpc::ClientContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::bigtable::admin::v2::AuthorizedView>,
      retry_policy(*current), backoff_policy(*current), idempotent,
      polling_policy(*current), __func__);
}

Status BigtableTableAdminConnectionImpl::DeleteAuthorizedView(
    google::bigtable::admin::v2::DeleteAuthorizedViewRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->DeleteAuthorizedView(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::bigtable::admin::v2::DeleteAuthorizedViewRequest const&
                 request) {
        return stub_->DeleteAuthorizedView(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::bigtable::admin::v2::Table>
BigtableTableAdminConnectionImpl::ModifyColumnFamilies(
    google::bigtable::admin::v2::ModifyColumnFamiliesRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->ModifyColumnFamilies(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::bigtable::admin::v2::ModifyColumnFamiliesRequest const&
                 request) {
        return stub_->ModifyColumnFamilies(context, options, request);
      },
      *current, request, __func__);
}

Status BigtableTableAdminConnectionImpl::DropRowRange(
    google::bigtable::admin::v2::DropRowRangeRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->DropRowRange(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::bigtable::admin::v2::DropRowRangeRequest const& request) {
        return stub_->DropRowRange(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::bigtable::admin::v2::GenerateConsistencyTokenResponse>
BigtableTableAdminConnectionImpl::GenerateConsistencyToken(
    google::bigtable::admin::v2::GenerateConsistencyTokenRequest const&
        request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GenerateConsistencyToken(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::bigtable::admin::v2::GenerateConsistencyTokenRequest const&
                 request) {
        return stub_->GenerateConsistencyToken(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::bigtable::admin::v2::CheckConsistencyResponse>
BigtableTableAdminConnectionImpl::CheckConsistency(
    google::bigtable::admin::v2::CheckConsistencyRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->CheckConsistency(request),
      [this](
          grpc::ClientContext& context, Options const& options,
          google::bigtable::admin::v2::CheckConsistencyRequest const& request) {
        return stub_->CheckConsistency(context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::bigtable::admin::v2::Backup>>
BigtableTableAdminConnectionImpl::CreateBackup(
    google::bigtable::admin::v2::CreateBackupRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto request_copy = request;
  auto const idempotent =
      idempotency_policy(*current)->CreateBackup(request_copy);
  return google::cloud::internal::AsyncLongRunningOperation<
      google::bigtable::admin::v2::Backup>(
      background_->cq(), current, std::move(request_copy),
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::bigtable::admin::v2::CreateBackupRequest const& request) {
        return stub->AsyncCreateBackup(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](google::cloud::CompletionQueue& cq,
                     std::shared_ptr<grpc::ClientContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::bigtable::admin::v2::Backup>,
      retry_policy(*current), backoff_policy(*current), idempotent,
      polling_policy(*current), __func__);
}

StatusOr<google::bigtable::admin::v2::Backup>
BigtableTableAdminConnectionImpl::GetBackup(
    google::bigtable::admin::v2::GetBackupRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetBackup(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::bigtable::admin::v2::GetBackupRequest const& request) {
        return stub_->GetBackup(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::bigtable::admin::v2::Backup>
BigtableTableAdminConnectionImpl::UpdateBackup(
    google::bigtable::admin::v2::UpdateBackupRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->UpdateBackup(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::bigtable::admin::v2::UpdateBackupRequest const& request) {
        return stub_->UpdateBackup(context, options, request);
      },
      *current, request, __func__);
}

Status BigtableTableAdminConnectionImpl::DeleteBackup(
    google::bigtable::admin::v2::DeleteBackupRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->DeleteBackup(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::bigtable::admin::v2::DeleteBackupRequest const& request) {
        return stub_->DeleteBackup(context, options, request);
      },
      *current, request, __func__);
}

StreamRange<google::bigtable::admin::v2::Backup>
BigtableTableAdminConnectionImpl::ListBackups(
    google::bigtable::admin::v2::ListBackupsRequest request) {
  request.clear_page_token();
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto idempotency = idempotency_policy(*current)->ListBackups(request);
  char const* function_name = __func__;
  return google::cloud::internal::MakePaginationRange<
      StreamRange<google::bigtable::admin::v2::Backup>>(
      current, std::move(request),
      [idempotency, function_name, stub = stub_,
       retry = std::shared_ptr<bigtable_admin::BigtableTableAdminRetryPolicy>(
           retry_policy(*current)),
       backoff = std::shared_ptr<BackoffPolicy>(backoff_policy(*current))](
          Options const& options,
          google::bigtable::admin::v2::ListBackupsRequest const& r) {
        return google::cloud::internal::RetryLoop(
            retry->clone(), backoff->clone(), idempotency,
            [stub](grpc::ClientContext& context, Options const& options,
                   google::bigtable::admin::v2::ListBackupsRequest const&
                       request) {
              return stub->ListBackups(context, options, request);
            },
            options, r, function_name);
      },
      [](google::bigtable::admin::v2::ListBackupsResponse r) {
        std::vector<google::bigtable::admin::v2::Backup> result(
            r.backups().size());
        auto& messages = *r.mutable_backups();
        std::move(messages.begin(), messages.end(), result.begin());
        return result;
      });
}

future<StatusOr<google::bigtable::admin::v2::Table>>
BigtableTableAdminConnectionImpl::RestoreTable(
    google::bigtable::admin::v2::RestoreTableRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto request_copy = request;
  auto const idempotent =
      idempotency_policy(*current)->RestoreTable(request_copy);
  return google::cloud::internal::AsyncLongRunningOperation<
      google::bigtable::admin::v2::Table>(
      background_->cq(), current, std::move(request_copy),
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::bigtable::admin::v2::RestoreTableRequest const& request) {
        return stub->AsyncRestoreTable(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](google::cloud::CompletionQueue& cq,
                     std::shared_ptr<grpc::ClientContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::bigtable::admin::v2::Table>,
      retry_policy(*current), backoff_policy(*current), idempotent,
      polling_policy(*current), __func__);
}

future<StatusOr<google::bigtable::admin::v2::Backup>>
BigtableTableAdminConnectionImpl::CopyBackup(
    google::bigtable::admin::v2::CopyBackupRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto request_copy = request;
  auto const idempotent =
      idempotency_policy(*current)->CopyBackup(request_copy);
  return google::cloud::internal::AsyncLongRunningOperation<
      google::bigtable::admin::v2::Backup>(
      background_->cq(), current, std::move(request_copy),
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::bigtable::admin::v2::CopyBackupRequest const& request) {
        return stub->AsyncCopyBackup(cq, std::move(context), std::move(options),
                                     request);
      },
      [stub = stub_](google::cloud::CompletionQueue& cq,
                     std::shared_ptr<grpc::ClientContext> context,
                     google::cloud::internal::ImmutableOptions options,
                     google::longrunning::GetOperationRequest const& request) {
        return stub->AsyncGetOperation(cq, std::move(context),
                                       std::move(options), request);
      },
      [stub = stub_](
          google::cloud::CompletionQueue& cq,
          std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::longrunning::CancelOperationRequest const& request) {
        return stub->AsyncCancelOperation(cq, std::move(context),
                                          std::move(options), request);
      },
      &google::cloud::internal::ExtractLongRunningResultResponse<
          google::bigtable::admin::v2::Backup>,
      retry_policy(*current), backoff_policy(*current), idempotent,
      polling_policy(*current), __func__);
}

StatusOr<google::iam::v1::Policy>
BigtableTableAdminConnectionImpl::GetIamPolicy(
    google::iam::v1::GetIamPolicyRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->GetIamPolicy(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::iam::v1::GetIamPolicyRequest const& request) {
        return stub_->GetIamPolicy(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::iam::v1::Policy>
BigtableTableAdminConnectionImpl::SetIamPolicy(
    google::iam::v1::SetIamPolicyRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->SetIamPolicy(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::iam::v1::SetIamPolicyRequest const& request) {
        return stub_->SetIamPolicy(context, options, request);
      },
      *current, request, __func__);
}

StatusOr<google::iam::v1::TestIamPermissionsResponse>
BigtableTableAdminConnectionImpl::TestIamPermissions(
    google::iam::v1::TestIamPermissionsRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  return google::cloud::internal::RetryLoop(
      retry_policy(*current), backoff_policy(*current),
      idempotency_policy(*current)->TestIamPermissions(request),
      [this](grpc::ClientContext& context, Options const& options,
             google::iam::v1::TestIamPermissionsRequest const& request) {
        return stub_->TestIamPermissions(context, options, request);
      },
      *current, request, __func__);
}

future<StatusOr<google::bigtable::admin::v2::CheckConsistencyResponse>>
BigtableTableAdminConnectionImpl::AsyncCheckConsistency(
    google::bigtable::admin::v2::CheckConsistencyRequest const& request) {
  auto current = google::cloud::internal::SaveCurrentOptions();
  auto request_copy = request;
  auto const idempotent =
      idempotency_policy(*current)->CheckConsistency(request_copy);
  auto retry = retry_policy(*current);
  auto backoff = backoff_policy(*current);
  return google::cloud::internal::AsyncRetryLoop(
      std::move(retry), std::move(backoff), idempotent, background_->cq(),
      [stub = stub_](
          CompletionQueue& cq, std::shared_ptr<grpc::ClientContext> context,
          google::cloud::internal::ImmutableOptions options,
          google::bigtable::admin::v2::CheckConsistencyRequest const& request) {
        return stub->AsyncCheckConsistency(cq, std::move(context),
                                           std::move(options), request);
      },
      std::move(current), std::move(request_copy), __func__);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_admin_internal
}  // namespace cloud
}  // namespace google

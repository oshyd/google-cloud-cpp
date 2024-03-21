// Copyright 2023 Google LLC
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
// source:
// google/cloud/compute/region_backend_services/v1/region_backend_services.proto

#include "google/cloud/compute/region_backend_services/v1/region_backend_services_client.h"
#include "google/cloud/compute/region_backend_services/v1/region_backend_services_connection_idempotency_policy.h"
#include "google/cloud/compute/region_backend_services/v1/region_backend_services_options.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/internal/getenv.h"
#include "google/cloud/polling_policy.h"
#include "google/cloud/testing_util/example_driver.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// clang-format off
// main-dox-marker: compute_region_backend_services_v1::RegionBackendServicesClient
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
  auto client = google::cloud::compute_region_backend_services_v1::
      RegionBackendServicesClient(
          google::cloud::compute_region_backend_services_v1::
              MakeRegionBackendServicesConnectionRest(options));
  //! [set-client-endpoint]
}

//! [custom-idempotency-policy]
class CustomIdempotencyPolicy
    : public google::cloud::compute_region_backend_services_v1::
          RegionBackendServicesConnectionIdempotencyPolicy {
 public:
  ~CustomIdempotencyPolicy() override = default;
  std::unique_ptr<google::cloud::compute_region_backend_services_v1::
                      RegionBackendServicesConnectionIdempotencyPolicy>
  clone() const override {
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
  auto options =
      google::cloud::Options{}
          .set<google::cloud::compute_region_backend_services_v1::
                   RegionBackendServicesConnectionIdempotencyPolicyOption>(
              CustomIdempotencyPolicy().clone())
          .set<google::cloud::compute_region_backend_services_v1::
                   RegionBackendServicesRetryPolicyOption>(
              google::cloud::compute_region_backend_services_v1::
                  RegionBackendServicesLimitedErrorCountRetryPolicy(3)
                      .clone())
          .set<google::cloud::compute_region_backend_services_v1::
                   RegionBackendServicesBackoffPolicyOption>(
              google::cloud::ExponentialBackoffPolicy(
                  /*initial_delay=*/std::chrono::milliseconds(200),
                  /*maximum_delay=*/std::chrono::seconds(45),
                  /*scaling=*/2.0)
                  .clone());
  auto connection = google::cloud::compute_region_backend_services_v1::
      MakeRegionBackendServicesConnectionRest(options);

  // c1 and c2 share the same retry policies
  auto c1 = google::cloud::compute_region_backend_services_v1::
      RegionBackendServicesClient(connection);
  auto c2 = google::cloud::compute_region_backend_services_v1::
      RegionBackendServicesClient(connection);

  // You can override any of the policies in a new client. This new client
  // will share the policies from c1 (or c2) *except* for the retry policy.
  auto c3 = google::cloud::compute_region_backend_services_v1::
      RegionBackendServicesClient(
          connection,
          google::cloud::Options{}
              .set<google::cloud::compute_region_backend_services_v1::
                       RegionBackendServicesRetryPolicyOption>(
                  google::cloud::compute_region_backend_services_v1::
                      RegionBackendServicesLimitedTimeRetryPolicy(
                          std::chrono::minutes(5))
                          .clone()));

  // You can also override the policies in a single call:
  // c3.SomeRpc(..., google::cloud::Options{}
  //     .set<google::cloud::compute_region_backend_services_v1::RegionBackendServicesRetryPolicyOption>(
  //       google::cloud::compute_region_backend_services_v1::RegionBackendServicesLimitedErrorCountRetryPolicy(10).clone()));
  //! [set-retry-policy]
}

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
  auto options =
      google::cloud::Options{}
          .set<google::cloud::compute_region_backend_services_v1::
                   RegionBackendServicesPollingPolicyOption>(
              google::cloud::GenericPollingPolicy<
                  google::cloud::compute_region_backend_services_v1::
                      RegionBackendServicesRetryPolicyOption::Type,
                  google::cloud::compute_region_backend_services_v1::
                      RegionBackendServicesBackoffPolicyOption::Type>(
                  google::cloud::compute_region_backend_services_v1::
                      RegionBackendServicesLimitedTimeRetryPolicy(
                          /*maximum_duration=*/std::chrono::minutes(45))
                          .clone(),
                  google::cloud::ExponentialBackoffPolicy(
                      /*initial_delay=*/std::chrono::seconds(10),
                      /*maximum_delay=*/std::chrono::minutes(2),
                      /*scaling=*/4.0)
                      .clone())
                  .clone());

  auto connection = google::cloud::compute_region_backend_services_v1::
      MakeRegionBackendServicesConnectionRest(options);

  // c1 and c2 share the same polling policies.
  auto c1 = google::cloud::compute_region_backend_services_v1::
      RegionBackendServicesClient(connection);
  auto c2 = google::cloud::compute_region_backend_services_v1::
      RegionBackendServicesClient(connection);
  //! [set-polling-policy]
}

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
    return google::cloud::compute_region_backend_services_v1::
        RegionBackendServicesClient(
            google::cloud::compute_region_backend_services_v1::
                MakeRegionBackendServicesConnectionRest(options));
  }
  //! [with-service-account]
  (argv.at(0));
}

void AutoRun(std::vector<std::string> const& argv) {
  namespace examples = ::google::cloud::testing_util;
  using ::google::cloud::internal::GetEnv;
  if (!argv.empty()) throw examples::Usage{"auto"};
  examples::CheckEnvironmentVariablesAreSet(
      {"GOOGLE_CLOUD_CPP_TEST_SERVICE_ACCOUNT_KEYFILE"});
  auto const keyfile =
      GetEnv("GOOGLE_CLOUD_CPP_TEST_SERVICE_ACCOUNT_KEYFILE").value();

  std::cout << "\nRunning SetClientEndpoint() example" << std::endl;
  SetClientEndpoint({});

  std::cout << "\nRunning SetRetryPolicy() example" << std::endl;
  SetRetryPolicy({});

  std::cout << "\nRunning SetPollingPolicy() example" << std::endl;
  SetPollingPolicy({});

  std::cout << "\nRunning WithServiceAccount() example" << std::endl;
  WithServiceAccount({keyfile});
}

}  // namespace

int main(int argc, char* argv[]) {  // NOLINT(bugprone-exception-escape)
  google::cloud::testing_util::Example example({
      {"set-client-endpoint", SetClientEndpoint},
      {"set-retry-policy", SetRetryPolicy},
      {"set-polling-policy", SetPollingPolicy},
      {"with-service-account", WithServiceAccount},
      {"auto", AutoRun},
  });
  return example.Run(argc, argv);
}

// Copyright 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef BIGTABLE_CLIENT_CHRONO_LITERALS_H_
#define BIGTABLE_CLIENT_CHRONO_LITERALS_H_

#include <chrono>

// TODO(coryan) - these are generally useful, consider submitting to abseil.io
namespace bigtable {
namespace chrono_literals {
constexpr std::chrono::milliseconds operator "" _ms(unsigned long long ms) {
  return std::chrono::milliseconds(ms);
}

constexpr std::chrono::microseconds operator "" _us(unsigned long long us) {
  return std::chrono::microseconds(us);
}

constexpr std::chrono::hours operator "" _h(unsigned long long h) {
  return std::chrono::hours(h);
}
}  // namespace chrono_literals
}  // namespace bigtable

#endif  // BIGTABLE_CLIENT_CHRONO_LITERALS_H_

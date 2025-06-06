# Copyright 2025 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

message(STATUS "Fetching pffft")
include(FetchContent)
FetchContent_Declare(
  pffft
  GIT_REPOSITORY "https://github.com/marton78/pffft.git"
  SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/pffft-src
)
FetchContent_GetProperties(pffft)
if(NOT pffft_POPULATED)
  FetchContent_Populate(pffft)
  # Manually include the necessary parts of pffft
  add_library(pffft STATIC ${pffft_SOURCE_DIR}/pffft.c)
  target_include_directories(pffft PUBLIC ${pffft_SOURCE_DIR})
endif()
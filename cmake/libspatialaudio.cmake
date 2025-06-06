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

# Note: We're using a custom version of libspatialaudio for now
# since there is a bug in the original version. If the bug is fixed
# we should move back to the original
message(STATUS "Fetching LibSpatialAudio")
include(FetchContent)
FetchContent_Declare(
  libspatialaudio
  GIT_REPOSITORY "https://github.com/WithACX/libspatialaudio.git"
  SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/libspatialaudio-src
)
FetchContent_MakeAvailable(libspatialaudio)
set(spatialaudio_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/libspatialaudio-src")
set(spatialaudio_BUILD_DIR "${CMAKE_BINARY_DIR}/_deps/libspatialaudio-build")

add_library(libspatialaudio INTERFACE)
target_compile_options(libspatialaudio INTERFACE "-w") # Silence is golden
target_link_libraries(libspatialaudio 
INTERFACE 
${spatialaudio_BUILD_DIR}/libspatialaudio.a)
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

message(STATUS "Fetching ZeroMQ")

set(ZMQ_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(CPPZMQ_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(WITH_GNUTLS OFF CACHE BOOL "" FORCE)
set(WITH_LIBSODIUM ON CACHE BOOL "" FORCE)
set(WITH_WS OFF CACHE BOOL "" FORCE)
set(WITH_WSS OFF CACHE BOOL "" FORCE)
set(WITH_TLS OFF CACHE BOOL "" FORCE)
set(ENABLE_WS OFF CACHE BOOL "" FORCE)
set(ENABLE_WSS OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
  zeromq
  GIT_REPOSITORY "https://github.com/zeromq/libzmq.git"
  SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/zeromq-src
  target_include_directories(zeromq PUBLIC ${zeromq_SOURCE_DIR}/include)
  CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF
)
FetchContent_MakeAvailable(zeromq)

message(STATUS "Fetching ZeroMQ CPP Wrapper")
include(FetchContent)
FetchContent_Declare(
  cppzmq
  GIT_REPOSITORY "https://github.com/zeromq/cppzmq.git"
  SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/cppzmq-src
  target_include_directories(cppzmq PUBLIC ${cppzmq_SOURCE_DIR})
)
FetchContent_MakeAvailable(cppzmq)
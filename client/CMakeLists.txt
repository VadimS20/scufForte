cmake_minimum_required(VERSION 3.10)

project(ClientApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(FetchContent)

FetchContent_Declare(argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse.git
  GIT_TAG        v3.1
)
FetchContent_MakeAvailable(argparse)

add_executable(CLIENT client.cpp)

target_link_libraries(CLIENT argparse::argparse)
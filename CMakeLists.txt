cmake_minimum_required(VERSION 3.16)
project(FORTE VERSION 0.1.0)

add_subdirectory(src)
include_directories(
    "./",
    "./src",
    "./src/typeLib",
    "./src/typeLib/modules"
)

add_executable(FORTE test.cpp)
target_link_libraries(FORTE TypeLib Modules)
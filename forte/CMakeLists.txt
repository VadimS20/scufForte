cmake_minimum_required(VERSION 3.16)
project(FORTE VERSION 0.1.0)

add_subdirectory(src)
add_subdirectory(lib)
include_directories(
    "./",
    "./src",
    "./src/typeLib",
    "./src/typeLib/modules"
    "./src/app"
    "./lib"
)

add_executable(FORTE test.cpp lib/pugixml.cpp)
target_link_libraries(FORTE App TypeLib Modules)
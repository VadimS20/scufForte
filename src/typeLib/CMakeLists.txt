add_subdirectory(modules)

set(SOURCE
    IFB.cpp
    globalOutputsList.cpp
    globalOutputsList.h
    IFB.h)

add_executable(${PROJECT_NAME} ${SOURCE})
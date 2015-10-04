cmake_minimum_required(VERSION 2.6)

project(v3d CXX)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
SET(CMAKE_CXX_FLAGS "-pthread -std=c++0x -O3")

find_package ( SDL REQUIRED )
find_package ( Threads REQUIRED )
include_directories(${SDL_INCLUDE_DIR})

file(
        GLOB_RECURSE
        source_files
        src/*
)

add_executable(
        v3d
        ${source_files}
)

target_link_libraries(
    v3d
    ${SDL_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
)

cmake_minimum_required(VERSION 2.6)

project(v3d C CXX)

SET(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
SET(CMAKE_CXX_FLAGS "-pthread -std=c++0x -O3")

find_package ( SDL REQUIRED )
find_package ( Threads REQUIRED )
include_directories(
        ${v3d_SOURCE_DIR}/src      
        ${SDL_INCLUDE_DIR}
)

file(
        GLOB_RECURSE
        source_files
        src/*
)

file(
        GLOB_RECURSE
        pugixml_files
        external/*
)

add_library(
        pugixml
        SHARED
        ${pugixml_files}
)

add_executable(
        v3d
        ${source_files}
)

target_link_libraries(
    v3d
    pugixml
    ${SDL_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
)

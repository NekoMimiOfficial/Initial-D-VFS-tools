cmake_minimum_required(VERSION 3.0.0)
project(initial-d-vfs-tools)

set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()
set (FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

include_directories(.)

add_library(utils SHARED ./src/utils.cpp)
add_library(vfs SHARED ./src/vfs.cpp)
add_library(counter SHARED ./src/counter.cpp)
add_library(cli SHARED ./src/cli.cpp)

add_executable(${PROJECT_NAME} ./src/main.cpp)
target_link_libraries(${PROJECT_NAME} utils)
target_link_libraries(${PROJECT_NAME} vfs)
target_link_libraries(${PROJECT_NAME} counter)
target_link_libraries(${PROJECT_NAME} cli)

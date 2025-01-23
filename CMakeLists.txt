cmake_minimum_required(VERSION 3.5.0)
project(initial-d-vfs-tools)

set (CMAKE_CXX_STANDARD_REQUIRED 20)
set (CMAKE_CXX_STANDARD 20)

set (FullOutputDir "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

include_directories(.)

add_library(utils SHARED ./src/utils.cpp)
add_library(vfs SHARED ./src/vfs.cpp)
add_library(cli SHARED ./src/cli.cpp)
add_library(binaryReader SHARED ./src/binaryReader.cpp)
add_library(box SHARED ./src/box.cpp)
add_library(crc SHARED ./src/crc.cpp)

add_executable(${PROJECT_NAME} ./src/main.cpp)
target_link_libraries(${PROJECT_NAME} utils)
target_link_libraries(${PROJECT_NAME} vfs)
target_link_libraries(${PROJECT_NAME} cli)
target_link_libraries(${PROJECT_NAME} binaryReader)
target_link_libraries(${PROJECT_NAME} box)
target_link_libraries(${PROJECT_NAME} crc)

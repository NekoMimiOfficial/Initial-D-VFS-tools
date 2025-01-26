cmake_minimum_required(VERSION 3.2.0)
project(crc-comunist-9000)

set (FullOutputDir "${CMAKE_SOURCE_DIR}/build/")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

include_directories(.)

add_executable(${PROJECT_NAME} ./main.cpp)

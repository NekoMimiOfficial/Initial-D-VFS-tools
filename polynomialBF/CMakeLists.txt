cmake_minimum_required(VERSION 3.2.0)
project(vfs-crc-poly-brute-9000)
set(DBG 1)

set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()
set (FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

include_directories(.)

add_library(utils SHARED ./utils.cpp)
add_library(binaryReader SHARED ./binaryReader.cpp)
add_library(box SHARED ./box.cpp)
add_library(crc SHARED ./crc.cpp)

add_compile_definitions(__DEBUG__=${DBG})

add_executable(${PROJECT_NAME} ./main.cpp)
target_link_libraries(${PROJECT_NAME} utils)
target_link_libraries(${PROJECT_NAME} binaryReader)
target_link_libraries(${PROJECT_NAME} box)
target_link_libraries(${PROJECT_NAME} crc)

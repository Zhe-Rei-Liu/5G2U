cmake_minimum_required(VERSION 3.5)

project(demoOpen62541)

set (EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)

add_definitions(-std=gnu99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/open62541/dir)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/open62541/src/pubusb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/open62541/deps)

add_executable(M-Publisher ${CMAKE_CURRENT_SOURCE_DIR}/src/M-Publisher.c ${CMAKE_CURRENT_SOURCE_DIR}/open62541/dir/open62541.c)
target_link_libraries(M-Publisher pthread)


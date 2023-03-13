cmake_minimum_required(VERSION 3.5)

project(demoOpen62541)

set (EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)

add_definitions(-std=gnu99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/open62541)

add_executable(CC-Client ${CMAKE_CURRENT_SOURCE_DIR}/src/CC-Client.c ${CMAKE_CURRENT_SOURCE_DIR}/open62541/open62541.c)

##add_executable(SYNts ${CMAKE_CURRENT_SOURCE_DIR}/src/SYNts.c)

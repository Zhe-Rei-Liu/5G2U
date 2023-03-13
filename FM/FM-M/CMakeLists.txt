cmake_minimum_required (VERSION 3.5)

project (pubsub_broker-less_demo)

set (EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)

add_definitions(-std=gnu99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/open62541/dir)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/open62541/src/pubsub)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/open62541/deps)

add_executable(M-Subscriber ${CMAKE_CURRENT_SOURCE_DIR}/src/M-Subscriber.c ${CMAKE_CURRENT_SOURCE_DIR}/open62541/dir/open62541.c)
target_link_libraries(M-Subscriber pthread)


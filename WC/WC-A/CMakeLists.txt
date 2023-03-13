cmake_minimum_required(VERSION 3.5)

project(demoOpen62541)

set (EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)

add_definitions(-std=gnu99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/open62541)

add_executable(A-Client ${CMAKE_CURRENT_SOURCE_DIR}/src/A-Client.c ${CMAKE_CURRENT_SOURCE_DIR}/open62541/open62541.c)
target_link_libraries(A-Client m)

add_executable(AS-Client ${CMAKE_CURRENT_SOURCE_DIR}/src/AS-Client.c ${CMAKE_CURRENT_SOURCE_DIR}/open62541/open62541.c)
target_link_libraries(AS-Client m)


cmake_minimum_required(VERSION 3.5)

project(demoOpen62541)

set (EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
## 使用gnu99編譯才有usleep()可以使用

add_definitions(-std=gnu99)

include_directories(${PROJECT_SOURCE_DIR}/open62541_ts)

add_executable(A-Server ${PROJECT_SOURCE_DIR}/src/A-Server.c ${PROJECT_SOURCE_DIR}/open62541_ts/open62541.c)
target_link_libraries(A-Server m)


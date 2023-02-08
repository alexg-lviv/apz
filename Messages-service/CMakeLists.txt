cmake_minimum_required(VERSION 3.23)
set(PROJECT_NAME Messages-service)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

find_path(LIBHTTPSERVER_INCLUDE_DIRS httpserverpp
        /usr/include
        /usr/include/httpserver
        /usr/local/include/
        /usr/local/include/httpserver
        )

find_library(LIBHTTPSERVER_LIBRARIES NAMES httpserver
        PATHS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        )

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBHTTPSERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBHTTPSERVER_LIBRARIES})




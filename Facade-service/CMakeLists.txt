cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME Facade_service)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

include(cmake/FindLibHttpServer.cmake)

include(cmake/FindLibCpr.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBHTTPSERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBHTTPSERVER_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBCPR_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBCPR_LIBRARIES})


find_package(spdlog REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)

if(IN_DOCKER)
    add_compile_definitions(IN_DOCKER)
    find_path(LIBUUID_INCLUDE_DIRS uuid
            /usr/include
            /usr/include/httpserver
            /usr/local/include/
            /usr/local/include/httpserver
            )

    find_library(LIBUUID_LIBRARIES NAMES uuid
            PATHS
            /usr/lib
            /usr/local/lib
            /opt/local/lib
            )

    target_include_directories(${PROJECT_NAME} PRIVATE ${LIBUUID_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${LIBUUID_LIBRARIES})
endif()
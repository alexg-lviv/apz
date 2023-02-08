cmake_minimum_required(VERSION 3.23)
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

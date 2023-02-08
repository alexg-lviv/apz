cmake_minimum_required(VERSION 3.23)
set(PROJECT_NAME Logging-service)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

include(cmake/FindLibHttpServer.cmake)

find_package(TBB REQUIRED)
target_link_libraries(${PROJECT_NAME} TBB::tbb)

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBHTTPSERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBHTTPSERVER_LIBRARIES})




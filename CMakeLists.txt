cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME apz_lab_1)
project(${PROJECT_NAME})

add_subdirectory(Facade-service)
add_subdirectory(Messages-service)
add_subdirectory(Logging-service)
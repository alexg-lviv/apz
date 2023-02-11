cmake_minimum_required(VERSION 3.23)
set(PROJECT_NAME apz_lab_2)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)


find_package(hazelcast-cpp-client CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE hazelcast-cpp-client::hazelcast-cpp-client)

#find_path(HazelClient_INCLUDE_DIRS hazelcast
#        /usr/include
#        /usr/include/hazelcast
#        /usr/local/include/
#        /usr/local/include/hazelcast
#        )
#
#find_library(HazelClient_LIBRARIES NAMES hazelcast
#        PATHS
#        /usr/lib
#        /usr/local/lib
#        /opt/local/lib/hazelcast
#        )
#
#
#target_include_directories(${PROJECT_NAME} PRIVATE ${HazelClient_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} ${HazelClient_LIBRARIES})
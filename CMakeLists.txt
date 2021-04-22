cmake_minimum_required(VERSION 3.0.0)
project(zmq-sandbox VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(cppzmq REQUIRED)

add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server cppzmq)
target_link_libraries(client cppzmq)
    
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

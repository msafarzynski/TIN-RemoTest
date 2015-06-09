cmake_minimum_required(VERSION 2.8)
project(Agent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp src/agent.cpp src/remoTestMessage.cpp src/tcp_server.cpp)
set(HEADER_FILES include/agent.h include/remoTestMessage.h include/tcp_server.h)
add_executable(Agent ${HEADER_FILES} ${SOURCE_FILES})
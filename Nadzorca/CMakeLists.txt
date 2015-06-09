cmake_minimum_required(VERSION 2.8)
project(Nadzorca)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp src/nadzorca.cpp src/remoTestMessage.cpp src/tcp_client.cpp src/FileParser.cpp)
set(HEADER_FILES include/nadzorca.h include/remoTestMessage.h include/tcp_client.h  include/FileParser.h)
add_executable(Nadzorca ${HEADER_FILES} ${SOURCE_FILES} )
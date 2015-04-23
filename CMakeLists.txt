cmake_minimum_required(VERSION 3.1)
project(TIN_RemoTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(TIN_RemoTest ${SOURCE_FILES}
    include/controller/controller.h
    include/controller/event_queue.hpp
    include/controller/events.h
    src/controller/controller.cpp
    src/controller/events.cpp)
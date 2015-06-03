cmake_minimum_required(VERSION 3.1)
project(TIN_RemoTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/agent/agent.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(TIN_RemoTest ${SOURCE_FILES}
    include/agent/agent_controller.h
    include/controller/controller.h
    include/controller/event_queue.hpp
    include/controller/events.h
    include/controller/timer.h
    include/model/agent_model.h
    include/model/executioner.h
    include/utils/lock.hpp
    include/utils/thread.hpp
    include/utils/scoped_lock.hpp
    src/agent/agent_controller.cpp
    src/controller/controller.cpp
    src/controller/events.cpp
    src/controller/timer.cpp
    src/utils/thread.cpp
    src/model/agent_model.cpp
    src/model/executioner.cpp
    )

find_package(Threads)
target_link_libraries (TIN_RemoTest ${CMAKE_THREAD_LIBS_INIT})
check_include_files(sys/timerfd.h USBI_TIMERFD_AVAILABLE)

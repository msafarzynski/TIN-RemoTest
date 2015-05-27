#include <chrono>
#include <thread>

#include "../../include/controller/events.h"
#include "../../include/controller/event_queue.hpp"
#include "../../include/controller/timer.h"

Timer::Timer(Event * event, EventQueue * queue, long milliseconds):
        Thread(), milliseconds(milliseconds), queue(queue), event(event)
{
}

void Timer::run()
{
    std::chrono::milliseconds duration(this->milliseconds);
    std::this_thread::sleep_for(duration);
    this->queue->push(this->event);
    this->finish();
}

#ifndef TIN_REMOTEST_TIMER_H
#define TIN_REMOTEST_TIMER_H

#include "events.h"
#include "event_queue.hpp"
#include "../utils/thread.hpp"

class Timer: Thread
{
public:
    Timer(Event*, BlockingQueue<Event>*, long);
    virtual void run();
private:
    long const milliseconds;
    Event* const event;
    BlockingQueue<Event>* const queue;
};

#endif //TIN_REMOTEST_TIMER_H

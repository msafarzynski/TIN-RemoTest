#ifndef TIN_REMOTEST_TIMER_H
#define TIN_REMOTEST_TIMER_H

#include <thread>
#include <assert.h>
#include "events.h"
#include "event_queue.hpp"
#include "utils/thread.hpp"

template <class T>
class Timer: public Thread
{
public:
    Timer(T event, BlockingQueue<T> * queue, long milliseconds): Thread(), milliseconds(milliseconds), queue(queue), event(event){};
    virtual void run()
    {
        assert(milliseconds>=0);
        std::chrono::milliseconds duration(this->milliseconds);
        std::this_thread::sleep_for(duration);
        this->queue->push(this->event);
        this->finish();
    };
private:
    long const milliseconds;
    T const event;
    BlockingQueue<T> * const queue;
};

typedef Timer<AgentEvent*> AgentTimer;

#endif //TIN_REMOTEST_TIMER_H

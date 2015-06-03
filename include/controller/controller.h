#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../utils/thread.hpp"
#include "events.h"
#include "event_queue.hpp"


class Controller : public Thread
{
protected:
    EventQueue* event_queue;

public:
    Controller(EventQueue*);
    virtual void run();
    void visit(StringEvent* event);
    void visit(UpdateScriptEvent* event);
};

#endif

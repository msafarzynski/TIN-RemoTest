#include <iostream>
#include "controller/controller.h"


Controller::Controller(EventQueue * queue): event_queue(queue)
{
}

void Controller::run()
{
    while(!isFinished())
    {
        Event* event = event_queue->pop();
        event->accept(this);
        delete event;
    }
}

void Controller::visit(StringEvent *event)
{
    std::cout<<"StringEvent: "<<event->getMessage()<<endl;
}

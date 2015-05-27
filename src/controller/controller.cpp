#include <typeindex>
#include <iostream>
#include <utility>

#include "../../include/controller/event_queue.hpp"
#include "../../include/controller/controller.h"


Controller::Controller(EventQueue* const event_queue) : event_queue(event_queue)
{
    this->strategyMap.insert(std::make_pair<std::type_index, StringStrategy*>
            (std::type_index(typeid(StringEvent)), new StringStrategy()));
}

void Controller::run()
{
    while(!isFinished())
    {
        Event* event = event_queue->pop();
        ControllerStrategy* strategy =
                strategyMap[std::type_index(typeid(*event))];
        strategy->react(event);
    }
}

void StringStrategy::react(Event* event)
{
    StringEvent* stringEven = dynamic_cast<StringEvent*>(event);
    std::cout<<"StringEvent: "<<stringEven->getMessage()<<endl;
}

ControllerStrategy::ControllerStrategy(){}

void ControllerStrategy::react(Event* event){}

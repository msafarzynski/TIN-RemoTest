#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unordered_map>
#include <typeinfo>
#include <typeindex>

class ControllerStrategy;

#include "event_queue.hpp"
#include "../utils/thread.hpp"


class Controller : public Thread
{
private:
    EventQueue* const event_queue;
    std::unordered_map<std::type_index, ControllerStrategy*> strategyMap;

public:
    Controller(EventQueue* const);
    virtual void run();
};


class ControllerStrategy
{
public:
    virtual void react(Event* event);
    ControllerStrategy();
};


class StringStrategy: public ControllerStrategy
{
public:
    virtual void react(Event* event);
};
#endif

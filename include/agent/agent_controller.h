#include "../controller/controller.h"

#ifndef TIN_REMOTEST_AGENT_CONTROLLER_H
#define TIN_REMOTEST_AGENT_CONTROLLER_H

class AgentController : public Controller
{
public:
    AgentController(EventQueue* const);
};


class StartExecutionStrategy: public ControllerStrategy
{
public:
    virtual void react(Event * event);
};


class StartExecutionAtTimeStrategy: public ControllerStrategy
{
public:
    virtual void react(Event * event);
};

#endif //TIN_REMOTEST_AGENT_CONTROLLLER_H

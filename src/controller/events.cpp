#include <string>
#include <iostream>
#include <agent/agent_controller.h>


Event::~Event() {}

StringEvent::StringEvent(string message): message(message)
{
}

StringEvent::~StringEvent(){}

string StringEvent::getMessage()
{
    return message;
}

void StringEvent::accept(Controller * controller)
{
    controller->visit(this);
}

StartExecutionAtTimeEvent::StartExecutionAtTimeEvent(time_t time) : time(time)
{
}

std::time_t StartExecutionAtTimeEvent::get_time()
{
    return time;
}

void StartExecutionAtTimeEvent::accept(AgentController * controller)
{
    controller->visit(this);
}

UpdateScriptEvent::UpdateScriptEvent(string script): script(script)
{
}

string UpdateScriptEvent::getScript()
{
    return script;
}

void UpdateScriptEvent::accept(AgentController * controller)
{
    controller->visit(this);
}

void StartExecutionEvent::accept(AgentController * controller)
{
    controller->visit(this);
}

void StopExecutionEvent::accept(AgentController * controller)
{
    controller->visit(this);
}

void PrintExecutionResultsEvent::accept(AgentController * controller)
{
    controller->visit(this);
}

UpdateTimeDifferenceEvent::UpdateTimeDifferenceEvent(std::time_t time): time(time)
{
}

void UpdateTimeDifferenceEvent::accept(AgentController * controller)
{
    controller->visit(this);
}

std::time_t UpdateTimeDifferenceEvent::getTime()
{
    return time;
}

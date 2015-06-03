#include <string>
#include <iostream>

#include "controller/events.h"
#include "controller/controller.h"

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

UpdateScriptEvent::UpdateScriptEvent(string script): script(script)
{
}

string UpdateScriptEvent::getScript()
{
    return script;
}

void UpdateScriptEvent::accept(Controller * controller)
{
    controller->visit(this);
}

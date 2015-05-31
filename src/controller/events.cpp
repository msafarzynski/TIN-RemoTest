#include <string>

#include "../../include/controller/events.h"


Event::~Event() {}

StringEvent::StringEvent(string message): message(message)
{
}

StringEvent::~StringEvent(){}

string StringEvent::getMessage()
{
    return message;
}

StartExecutionAtTimeEvent::StartExecutionAtTimeEvent(time_t time) : time(time)
{
}

std::time_t StartExecutionAtTimeEvent::get_time()
{
    return time;
}

UpdateScriptEvent::UpdateScriptEvent(string const script): script(script)
{
}

string UpdateScriptEvent::getScript()
{
    return script;
}

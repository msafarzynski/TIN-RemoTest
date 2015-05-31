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

StartExecutionEventAtTime::StartExecutionEventAtTime(time_t time) : time(time)
{
}

std::time_t StartExecutionEventAtTime::get_time()
{
    return time;
}

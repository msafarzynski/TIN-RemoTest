#include <string>

#include "../../include/controller/events.h"


StringEvent::StringEvent(string message): message(message)
{
}

string StringEvent::getMessage()
{
    return message;
}

Event::~Event() {}

StringEvent::~StringEvent(){}

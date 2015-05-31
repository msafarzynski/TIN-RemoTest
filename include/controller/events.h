#include <string>
#include <ctime>

#ifndef EVENTS_H
#define EVENTS_H

using namespace std;
class Event
{
public:
    virtual ~Event();
};

class StringEvent: public Event
{
private:
    const string message;
public:
    virtual ~StringEvent();
    virtual string getMessage();
    StringEvent(string message);
};

class StartExecutionEvent: public Event
{
};

class StartExecutionEventAtTime: public Event
{
private:
    const std::time_t time;
public:
    StartExecutionEventAtTime(std::time_t);
    std::time_t get_time();
};

#endif

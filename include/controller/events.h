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


class StartExecutionAtTimeEvent: public Event
{
private:
    const std::time_t time;
public:
    StartExecutionAtTimeEvent(std::time_t);
    std::time_t get_time();
};


class UpdateScriptEvent: public Event
{
private:
    const string script;
public:
    UpdateScriptEvent(const string);
    string getScript();
};

#endif

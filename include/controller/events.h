#ifndef EVENTS_H
#define EVENTS_H

#include <string>
#include <ctime>

using namespace std;

class Controller;
class AgentController;


class Event
{
public:
    virtual ~Event();
    virtual void accept(Controller *) = 0;
};


class AgentEvent
{
public:
    virtual ~AgentEvent(){};
    virtual void accept(AgentController *) = 0;
};


class StringEvent: public Event
{
private:
    const string message;
public:
    virtual ~StringEvent();
    virtual string getMessage();
    StringEvent(string message);
    void accept(Controller*);
};


class StartExecutionEvent: public AgentEvent
{
public:
    void accept(AgentController*);
};


class StartExecutionAtTimeEvent: public Event
{
private:
    const std::time_t time;
public:
    StartExecutionAtTimeEvent(std::time_t);
    std::time_t get_time();
};


class StopExecutionEvent: public AgentEvent
{
public:
    void accept(AgentController*);
};


class PrintExecutionResultsEvent: public AgentEvent
{
public:
    void accept(AgentController*);
};


class UpdateScriptEvent: public AgentEvent
{
private:
    const string script;
public:
    UpdateScriptEvent(string);
    string getScript();
    void accept(AgentController*);
};

#endif

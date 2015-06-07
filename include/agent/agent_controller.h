#ifndef TIN_REMOTEST_AGENT_CONTROLLER_H
#define TIN_REMOTEST_AGENT_CONTROLLER_H

#include "controller/controller.h"
#include "model/agent_model.h"


class AgentController : public Thread
{
protected:
    AgentQueue * agent_queue;

public:
    AgentController(AgentQueue * const, AgentModel* const);
    void visit(StartExecutionEvent*);
    void visit(StartExecutionAtTimeEvent*);
    void visit(StopExecutionEvent*);
    void visit(UpdateScriptEvent*);
    void run();
private:
    AgentModel * const model;
};

#endif //TIN_REMOTEST_AGENT_CONTROLLLER_H

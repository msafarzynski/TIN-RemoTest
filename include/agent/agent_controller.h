#include "../controller/controller.h"
#include "../model/agent_model.h"

#ifndef TIN_REMOTEST_AGENT_CONTROLLER_H
#define TIN_REMOTEST_AGENT_CONTROLLER_H

class AgentController : public Controller
{
public:
    AgentController(EventQueue * const, AgentModel* const);
    void visit(StartExecutionEvent*);
    void visit(StartExecutionAtTimeEvent*);
    void visit(UpdateScriptEvent*);
private:
    const AgentModel * const model;
};

#endif //TIN_REMOTEST_AGENT_CONTROLLLER_H

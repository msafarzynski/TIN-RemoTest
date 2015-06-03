#include <iostream>
#include "../../include/agent/agent_controller.h"


AgentController::AgentController(EventQueue * const event_queue, AgentModel* model):
        Controller(event_queue), model(model)
{
}

void AgentController::visit(StartExecutionEvent * event)
{
    std::cout<<"Start Execution"<<std::endl;
}

void AgentController::visit(StartExecutionAtTimeEvent * event)
{
    std::cout<<"Start execution at time: "<<event->get_time()<<std::endl;
}

void AgentController::visit(UpdateScriptEvent * event)
{
    std::cout<<"Update script: "<<event->getScript()<<std::endl;
}

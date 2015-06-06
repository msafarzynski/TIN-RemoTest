#include <iostream>
#include "agent/agent_controller.h"


void AgentController::run()
{
    while(!isFinished())
    {
        AgentEvent* event = agent_queue->pop();
        event->accept(this);
        delete event;
    }

}

AgentController::AgentController(AgentQueue * const agent_queue, AgentModel* model):
        agent_queue(agent_queue), model(model)
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
    model->updateScript(event->getScript());
}

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
    model->execute();
}

void AgentController::visit(StartExecutionAtTimeEvent * event)
{
    if (timer != NULL)
    {
        timer->stop();
    }
    timer = new AgentTimer(dynamic_cast<AgentEvent*>(new StartExecutionEvent()), agent_queue,
                           getSecondsUntil(event->get_time()));
    timer->start();
}

void AgentController::visit(UpdateScriptEvent * event)
{
    model->updateScript(event->getScript());
}

void AgentController::visit(StopExecutionEvent * event)
{
    model->stopExecution();
}

void AgentController::visit(PrintExecutionResultsEvent * event)
{
    std::cout<<"RESULT: \n"<<model->getExecutionResult();
}

std::time_t AgentController::getCurrentTime()
{
    return std::time(0) - timeDifference;
}

long AgentController::getSecondsUntil(time_t time)
{
    return time - getCurrentTime();
}

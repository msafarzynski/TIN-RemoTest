#include <iostream>
#include "agent/agent.h"
#include "controller/event_queue.hpp"
#include "agent/agent_controller.h"
#include "controller/timer.hpp"

Agent::Agent()
{
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    AgentQueue * queue = new AgentQueue();
    AgentModel* model = new AgentModel();
    AgentController* controller = new AgentController(queue, model);

    string script = "ping 8.8.8.8";
    queue->push(new UpdateScriptEvent(script));
    queue->push(new StartExecutionEvent());
    AgentTimer* timer = new AgentTimer(dynamic_cast<AgentEvent*>(new StopExecutionEvent()), queue, 2000);
    timer->start();
    AgentTimer* timer2 = new AgentTimer(dynamic_cast<AgentEvent*>(new PrintExecutionResultsEvent()), queue, 5000);
    timer2->start();

    controller->run();
    return 0;
}

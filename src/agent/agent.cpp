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

    std::time_t result = std::time(0);
    std::cout << std::asctime(std::localtime(&result))
    << result << " seconds since the Epoch\n";
    string script = "ls";
    queue->push(new UpdateScriptEvent(script));
    queue->push(new StartExecutionEvent());

    controller->run();
    return 0;
}

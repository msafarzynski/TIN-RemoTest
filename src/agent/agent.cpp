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
    string script = "ping 8.8.8.8";
    AgentTimer* timer = new AgentTimer(dynamic_cast<AgentEvent*>(new UpdateScriptEvent(script)), queue, 2000);
    timer->start();
    controller->run();
    return 0;
}

#include <iostream>
#include "../../include/agent/agent.h"
#include "../../include/controller/event_queue.hpp"
#include "../../include/agent/agent_controller.h"
#include "../../include/controller/timer.h"

Agent::Agent()
{
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    EventQueue* queue = new EventQueue();
    AgentController* controller = new AgentController(queue);

    Timer* timer = new Timer(dynamic_cast<Event*>(new StringEvent(string("mess"))), queue, 2000);
    timer->start();
    controller->run();
    return 0;
}

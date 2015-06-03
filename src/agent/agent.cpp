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
    AgentModel* model = new AgentModel();
    AgentController* controller = new AgentController(queue, model);

    std::time_t result = std::time(0);
    std::cout << std::asctime(std::localtime(&result))
    << result << " seconds since the Epoch\n";
    Timer* timer = new Timer(dynamic_cast<Event*>(new StringEvent(string("mess"))), queue, 200);
    timer->start();
////    system("ping 8.8.8.8");
    string script = "ping 8.8.8.8";
    Timer* timer2 = new Timer(dynamic_cast<Event*>(new UpdateScriptEvent(script)), queue, 2000);
    timer2->start();
    controller->run();
    return 0;
}

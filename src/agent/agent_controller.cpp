#include <iostream>
#include "../../include/agent/agent_controller.h"
#include "../../include/controller/event_queue.hpp"


AgentController::AgentController(EventQueue * const event_queue, AgentModel* model):
        Controller(event_queue), model(model)
{
    this->strategyMap.insert(std::make_pair<std::type_index, StartExecutionStrategy*>
                                     (std::type_index(typeid(StartExecutionEvent)), new StartExecutionStrategy()));
    this->strategyMap.insert(std::make_pair<std::type_index, StartExecutionAtTimeStrategy*>
                                     (std::type_index(typeid(StartExecutionEventAtTime)),
                                      new StartExecutionAtTimeStrategy()));

}

void StartExecutionStrategy::react(Event *event)
{
    std::cout<<"Start execution strategy"<<std::endl;
}

void StartExecutionAtTimeStrategy::react(Event *event)
{
    StartExecutionEventAtTime* execution_event = dynamic_cast<StartExecutionEventAtTime*>(event);
    std::cout<<"Start at time execution strategy. Time: "<<execution_event->get_time()<<std::endl;
}

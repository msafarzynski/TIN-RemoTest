#include "model/agent_model.h"

AgentModel::AgentModel(Executioner *executioner): executioner(executioner)
{
};

AgentModel::AgentModel()
{
    this->executioner = new Executioner();
}

#include "model/agent_model.h"

AgentModel::AgentModel(Executioner *executioner): executioner(executioner)
{
};

AgentModel::AgentModel()
{
    this->executioner = new Executioner();
}

void AgentModel::updateScript(std::string script)
{
    executioner->updateScript(script);
}

std::string AgentModel::getScript()
{
    return executioner->getScript();
}

void AgentModel::execute()
{
    executioner->start();
}

std::string AgentModel::getExecutionResult()
{
    return executioner->getResult();
}

void AgentModel::stopExecution()
{
    executioner->stop();
}

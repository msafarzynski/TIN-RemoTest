#ifndef TIN_REMOTEST_MODEL_H
#define TIN_REMOTEST_MODEL_H

#include "executioner.h"

class AgentModel
{
public:
    AgentModel(Executioner*);
    AgentModel();
private:
    Executioner* executioner;
};

#endif //TIN_REMOTEST_MODEL_H

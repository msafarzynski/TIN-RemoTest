#include "model/executioner.h"


Executioner::Executioner()
{
};

Executioner::Executioner(std::string script) : script(script)
{
};

void Executioner::updateScript(std::string script)
{
    this->script=script;
};

std::string Executioner::getSctipt()
{
    return script;
}

void Executioner::execute()
{
    // TODO
};

void Executioner::executeScript(std::string script)
{
    this->updateScript(script);
    this->execute();
};

void Executioner::stopExecution()
{
    //TODO
};

void Executioner::run()
{
    this->execute();
}

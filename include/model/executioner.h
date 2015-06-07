#ifndef TIN_REMOTEST_EXECUTIONER_H
#define TIN_REMOTEST_EXECUTIONER_H

#include <string>
#include "utils/thread.hpp"

class Executioner
{
private:
    std::string script;
    std::string result;
    bool run = false;
public:
    Executioner();
    Executioner(std::string);
    void updateScript(std::string);
    std::string getScript();
    std::string getResult();
    void execute();
    void executeScript(std::string);
    void stopExecution();
};
#endif //TIN_REMOTEST_EXECUTIONER_H

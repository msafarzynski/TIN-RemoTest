#ifndef TIN_REMOTEST_EXECUTIONER_H
#define TIN_REMOTEST_EXECUTIONER_H

#include <string>
#include "../utils/thread.hpp"

class Executioner: public Thread
{
private:
    std::string script;
public:
    Executioner();
    Executioner(std::string);
    void updateScript(std::string);
    void execute();
    void executeScript(std::string);
    void stopExecution();
    void run();
};
#endif //TIN_REMOTEST_EXECUTIONER_H

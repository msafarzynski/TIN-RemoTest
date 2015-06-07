#ifndef TIN_REMOTEST_EXECUTIONER_H
#define TIN_REMOTEST_EXECUTIONER_H

#include <string>
#include "utils/thread.hpp"

class Executioner: public Thread
{
private:
    std::string script;
    std::string result;
    void run();

public:
    Executioner();
    Executioner(std::string);
    void updateScript(std::string);
    std::string getScript();
    std::string getResult();
    void executeScript(std::string);
};
#endif //TIN_REMOTEST_EXECUTIONER_H

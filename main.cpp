#include <iostream>
#include "include/controller/event_queue.hpp"
#include "include/controller/controller.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    EventQueue* queue = new EventQueue();
    Controller* controller = new Controller(queue);
    controller->run();
    return 0;
}

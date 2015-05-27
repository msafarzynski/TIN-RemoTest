#include <iostream>
#include "include/controller/event_queue.hpp"
#include "include/controller/controller.h"
#include "include/controller/timer.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    EventQueue* queue = new EventQueue();
    Controller* controller = new Controller(queue);
    Timer* timer = new Timer(dynamic_cast<Event*>(new StringEvent(string("mess"))), queue, 2000);
    timer->start();
    controller->run();
    return 0;
}

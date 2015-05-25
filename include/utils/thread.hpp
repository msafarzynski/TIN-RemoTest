#ifndef TIN_REMOTEST_THREAD_HPP
#define TIN_REMOTEST_THREAD_HPP

#include <pthread.h>

#include "lock.hpp"

class Thread
{
public:
    Thread();
    virtual ~Thread();
    void start();
    void join();
    void stop();
    bool isFinished() const;

protected:
    virtual void run() = 0;
    void finish();

private:
    static void* runWrapper(void* thread);
    bool finished_;
    mutable Lock lock_;
    pthread_t thread_;
};

#endif //TIN_REMOTEST_THREAD_HPP

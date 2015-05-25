#ifndef TIN_REMOTEST_SCOPED_LOCK_HPP
#define TIN_REMOTEST_SCOPED_LOCK_HPP

#include <boost/noncopyable.hpp>
#include "lock.hpp"
#include <iostream>

class ScopedLock : public boost::noncopyable
{
public:
    ScopedLock(Lock &lock) : lock_(lock)
    {
        lock_.lock();
    }

    ~ScopedLock()
    {
        lock_.unlock();
    }

private:
    Lock &lock_;
};

#endif //TIN_REMOTEST_SCOPED_LOCK_HPP

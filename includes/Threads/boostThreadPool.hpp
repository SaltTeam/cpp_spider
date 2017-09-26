//
// Created by Grégoire on 26/09/2017.
//

#ifndef BOOSTTHREADPOOL_HPP
#define BOOSTTHREADPOOL_HPP

#include <boost/asio/io_service.hpp>
#include <boost/atomic/atomic.hpp>
#include <boost/lockfree/lockfree_forward.hpp>
#include <memory>
#include <queue>
#include "Service.hpp"
#include "IThreadGroup.hpp"

class boostThreadPool {
public:
    void addClient();
    void run();
    void stop();
public:
    boostThreadPool();
    ~boostThreadPool();

private:
    std::unique_ptr<IThreadGroup>          pool;
    friend boost::atomic_bool              poolContinue;
    friend boost::atomic<std::queue>       clientqueue;
    Service                                service;
};


#endif //BOOSTTHREADPOOL_HPP

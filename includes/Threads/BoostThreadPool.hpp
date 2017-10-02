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
#include "IThreadPool.hpp"

class BoostThreadPool: public IThreadPool {
public:
    void addClient();
    void run();
    void stop();
public:
    BoostThreadPool();
    ~BoostThreadPool();

private:
    friend class Service;
    std::unique_ptr<IThreadGroup>   pool;
    boost::atomic_bool              poolContinue;
    boost::atomic<std::queue<int>>  clientqueue;
    Service                         service;
};


#endif //BOOSTTHREADPOOL_HPP
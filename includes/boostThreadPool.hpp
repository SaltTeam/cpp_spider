//
// Created by Grégoire on 26/09/2017.
//

#ifndef BOOSTTHREADPOOL_HPP
#define BOOSTTHREADPOOL_HPP

#include <boost/asio/io_service.hpp>
#include <memory>
#include "IThreadGroup.hpp"

class boostThreadPool {
public:
    void init();
    void run();
    void stop();
public:
    boostThreadPool();
    ~boostThreadPool();

private:
    std::unique_ptr<IThreadGroup>   pool;
    boost::asio::io_service         service;
};


#endif //BOOSTTHREADPOOL_HPP

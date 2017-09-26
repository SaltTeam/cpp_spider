//
// Created by Grégoire on 26/09/2017.
//

#ifndef BOOSTTHREADGROUP_HPP
#define BOOSTTHREADGROUP_HPP

#include <boost/thread/thread.hpp>

class boostThreadGroup {
public:
    void init(int nbThreads);
    void joinAll();
    void interruptAll();

public:
    boostThreadGroup();
    ~boostThreadGroup();

private:
    boost::thread_group group;
};


#endif //CPP_SPIDER_BOOSTTHREADGROUP_HPP

//
// Created by Grégoire on 26/09/2017.
//

#ifndef BOOSTTHREADGROUP_HPP
#define BOOSTTHREADGROUP_HPP

#include <boost/thread/thread.hpp>
#include "IThreadGroup.hpp"

class BoostThreadGroup: public IThreadGroup {
public:
    void createThreads();
    void joinAll();
    void interruptAll();

public:
    BoostThreadGroup();
    ~BoostThreadGroup();

private:
    boost::thread_group group;
};


#endif //BOOSTTHREADGROUP_HPP

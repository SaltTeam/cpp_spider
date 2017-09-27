//
// Created by Grégoire on 26/09/2017.
//

#ifndef ITHREADGROUP_HPP
#define ITHREADGROUP_HPP


class IThreadGroup {
public:
    virtual void joinAll() = 0;
    virtual void interruptAll() = 0;
    virtual void createThreads() = 0;
    virtual ~IThreadGroup() {};
};


#endif //ITHREAD_HPP

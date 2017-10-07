//
// Created by loens_g on 07/10/17.
//

#ifndef CPP_SPIDER_ITHREAD_H
#define CPP_SPIDER_ITHREAD_H


class IThread {
public:
    virtual void createThread(std::function<void()> funcptr) = 0;
    virtual void threadJoin() = 0;
    virtual ~IThread() = 0;
};


#endif //CPP_SPIDER_ITHREAD_H

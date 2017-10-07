//
// Created by loens_g on 07/10/17.
//

#ifndef CPP_SPIDER_ITHREAD_H
#define CPP_SPIDER_ITHREAD_H

#include <bits/unique_ptr.h>
#include "Protocol/IProtocol.hpp"

namespace spider {

    class IThread {
    public:
        virtual void createThread(std::unique_ptr<IProtocol> &protocol) = 0;

        virtual void threadJoin() = 0;

        virtual ~IThread() = 0;
    };
};

#endif //CPP_SPIDER_ITHREAD_H

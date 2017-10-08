//
// Created by loens_g on 07/10/17.
//

#ifndef CPP_SPIDER_ITHREAD_H
#define CPP_SPIDER_ITHREAD_H

#include <memory>
#include "Protocol/IProtocol.hpp"

/// \namespace spider
namespace spider {

    /// \interface IThread
    class IThread {
    public:

        /// \brief Create a new thread for the protocol run function
        virtual void createThread(std::unique_ptr<IProtocol> &protocl) = 0;

        /// \brief Create thread for net run service
        virtual void createNetThread() = 0;

        /// \brief Create thread for server net run service
        virtual void createNetServThread() = 0;

        /// \brief Join thread
        virtual void threadJoin() = 0;
    };
};

#endif //CPP_SPIDER_ITHREAD_H

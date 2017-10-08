//
// Created by loens_g on 07/10/17.
//

#ifndef CPP_SPIDER_BOOSTTHREAD_HPP
#define CPP_SPIDER_BOOSTTHREAD_HPP

#include <boost/thread/thread.hpp>
#include <Protocol/IProtocol.hpp>
#include "IThread.hpp"

/// \brief spider
namespace spider {

    /// \class BoostThread inherit from IThread
    class BoostThread : public IThread {
    public:
        /// \brief deleted constructor copy
        BoostThread(BoostThread const &copy) = delete;

        /// \brief default constructor
        BoostThread();

        /// \brief default destructor
         virtual ~BoostThread();

    public:

        /// \brief Create a new thread for the protocol run function
        void threadJoin() override;

        /// \brief Create thread for net run service
        void createThread(std::unique_ptr<IProtocol> &proto) override;

        /// \brief Create thread for server net run service
        void createNetThread() override;

        /// \brief Join thread
        void createNetServThread() override;

    private:
        /// \brief boost thread
        boost::thread thread;
    };

};
#endif //CPP_SPIDER_BOOSTTHREAD_HPP

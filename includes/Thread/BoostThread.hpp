//
// Created by loens_g on 07/10/17.
//

#ifndef CPP_SPIDER_BOOSTTHREAD_HPP
#define CPP_SPIDER_BOOSTTHREAD_HPP

#include <boost/thread/thread.hpp>
#include <Protocol/IProtocol.hpp>
#include "IThread.hpp"

namespace spider {

    class BoostThread : public IThread {
    public:
        BoostThread(BoostThread const &copy) = delete;

      BoostThread();

        ~BoostThread();

    public:
        void threadJoin() override;

        void createThread(std::unique_ptr<IProtocol> &proto) override;

    private:
        boost::thread thread;
    };

};
#endif //CPP_SPIDER_BOOSTTHREAD_HPP

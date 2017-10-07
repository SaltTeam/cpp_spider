//
// Created by loens_g on 07/10/17.
//

#ifndef CPP_SPIDER_BOOSTTHREAD_HPP
#define CPP_SPIDER_BOOSTTHREAD_HPP

#include <boost/thread/thread.hpp>
#include "IThread.hpp"

namespace spider {

    class BoostThread : public IThread {
    public:
        BoostThread(BoostThread const &copy) = delete;

        BoostThread(std::function<void()> funcptr);

        ~BoostThread();

    public:
        void threadJoin() override;

        void createThread(std::function<void()> funcptr) override;

    private:
        boost::thread thread;
    };

};
#endif //CPP_SPIDER_BOOSTTHREAD_HPP

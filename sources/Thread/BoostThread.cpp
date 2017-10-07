//
// Created by loens_g on 07/10/17.
//

#include "Thread/BoostThread.hpp"

namespace spider
{


BoostThread::BoostThread(std::function<void()> funcptr) :
        thread(funcptr) {

}

BoostThread::~BoostThread() {

}

void BoostThread::threadJoin() {
    thread.join();
}

void BoostThread::createThread(std::function<void()> funcptr) {
    thread = boost::thread(funcptr);
}

};
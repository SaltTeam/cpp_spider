//
// Created by loens_g on 07/10/17.
//

#include <Protocol/IProtocol.hpp>
#include "Thread/BoostThread.hpp"

namespace spider
{


BoostThread::BoostThread(){

}

BoostThread::~BoostThread() {

}

void BoostThread::threadJoin() {
    thread.join();
}

void BoostThread::createThread(std::unique_ptr<IProtocol> &proto) {
    thread = boost::thread(proto.get()->run());
}

};
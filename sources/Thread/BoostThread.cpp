//
// Created by loens_g on 07/10/17.
//

#include <iostream>
#include <Protocol/IProtocol.hpp>
#include "Thread/BoostThread.hpp"

namespace spider
{

  BoostThread::BoostThread() {

  }

BoostThread::~BoostThread() = default;

void BoostThread::threadJoin() {
    thread.join();
}

void BoostThread::createThread(std::unique_ptr<IProtocol> &proto) {
  std::cout << "before thread" << std::endl;
  thread = boost::thread(boost::bind(&IProtocol::run, proto.get()));
}

};
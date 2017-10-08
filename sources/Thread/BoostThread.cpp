/*
** BoostThread.cpp for test_spider in /home/soszyn_h/rendu/cpp_spider/sources/Thread/BoostThread.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Sun Oct 08 10:59:56 2017 Hugo SOSZYNSKI
** Last update Sun Oct 08 10:59:56 2017 Hugo SOSZYNSKI
*/

#include <iostream>
#include "Protocol/IProtocol.hpp"
# ifdef WIN32

#include "Protocol/ClientProtocol.hpp"

# else

#include "Protocol/ServerProtocol.hpp"

# endif
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
  thread = boost::thread(boost::bind(&IProtocol::run, proto.get()));
}

  void BoostThread::createNetThread()
  {
    thread = boost::thread(boost::bind(&spider::runNetwork));
  }


  void BoostThread::createNetServThread()
  {
    thread = boost::thread(boost::bind(&spider::runServerNetwork));
  }
};
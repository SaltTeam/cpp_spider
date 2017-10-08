/*
** ServerCore.c for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/ServerCore.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Fri Sep 29 08:08:01 2017 Maxime PILLON
** Last update Fri Sep 29 08:08:01 2017 Maxime PILLON
*/

#include <boost/make_unique.hpp>
#include "logger/Logger.hpp"
#include "Thread/IThread.hpp"
#include "Thread/BoostThread.hpp"
#include "ServerCore.hpp"

spider::ServerCore::ServerCore() : _db(spider::Sqlite()),
				   _proto(spider::ServerProtocol())
{
  logger::Logger &logger  = logger::Logger::getLogger();

  logger.log(logger::INFO, "Create ServerCore object");
  _db.open("db.sqlite");
  _db.createDb();
}

spider::ServerCore::~ServerCore()
{
  logger::Logger	&logger  = logger::Logger::getLogger();

  logger.log(logger::INFO, "Closing DB");
  _db.close();
}

void spider::ServerCore::run()
{
  logger::Logger &logger  = logger::Logger::getLogger();
  std::unique_ptr<spider::IThread>	threadnet(boost::make_unique<BoostThread>());

  if (threadnet)
  {
    logger.log(logger::DEBUG, "Start the net thread");
    threadnet.get()->createNetThread();
  }
  while(1)
  {
   _proto.run();
    _db.treat(_proto.getInfo());
  }
}
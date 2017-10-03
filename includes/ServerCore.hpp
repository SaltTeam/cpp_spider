/*
** core.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/core.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Fri Sep 29 07:58:37 2017 Maxime PILLON
** Last update Fri Sep 29 07:58:37 2017 Maxime PILLON
*/

#pragma once

# include "Threads/BoostThreadPool.hpp"
# include "Database/Sqlite.hpp"
# include "Protocol/Protocol.hpp"

namespace spider
{
  class ServerCore
  {
  protected:
    typedef boost::atomic<std::queue<t_unserialized>> unserialized_queue;

    IDatabase			_db;
    IProtocol			_proto;
    IThreadPool			_pool;
    unserialized_queue		data;

  public:
    ServerCore();
    ~ServerCore();

    void run();
  };
}
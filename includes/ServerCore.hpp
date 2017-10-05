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

# include "Database/Sqlite.hpp"
# include "Protocol/ServerProtocol.hpp"

namespace spider
{
  class ServerCore
  {
  protected:

    IDatabase			_db;
    IProtocol			_proto;

  public:
    ServerCore();
    ~ServerCore();

    void run();
  };
}
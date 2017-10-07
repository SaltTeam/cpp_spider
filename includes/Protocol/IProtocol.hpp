/*
** Protocol.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/Protocol.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Mon Sep 25 13:31:02 2017 Maxime PILLON
** Last update Mon Sep 25 13:31:02 2017 Maxime PILLON
*/

#pragma once

# include <queue>
# include "dataStructure.hpp"

namespace spider
{


  class IProtocol {
  public:
    typedef std::queue<t_unserialized> unserialized_queue;

    virtual ~IProtocol(){}

    virtual bool		connect() = 0;

    virtual void		sendData() = 0;

    virtual void		sendPing() = 0;

    virtual void		run() = 0;
  };
}
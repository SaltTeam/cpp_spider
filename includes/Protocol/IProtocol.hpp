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

/// \namespace spider
namespace spider
{

  /// \class IProtocol
  class IProtocol {
  public:
    typedef std::queue<t_unserialized> unserialized_queue;

    virtual ~IProtocol(){}

    /// \brief check if a ping command has been sent and respond to it
    virtual void		checkPing() = 0;

    /// \brief run the main function of the protocol
    virtual void		run() = 0;
  };
}
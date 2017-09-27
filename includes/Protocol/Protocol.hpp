/*
** Protocol.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/Protocol/Protocol.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Sep 27 13:29:22 2017 Maxime PILLON
** Last update Wed Sep 27 13:29:22 2017 Maxime PILLON
*/

#pragma once

#include "IProtocol.hpp"

class Protocol : public IProtocol
{
protected:

public:
  Protocol();
  ~Protocol();

  void		sendData();
  void		sendPing();
  bool		hasCommand();
  void		getCommand();
};
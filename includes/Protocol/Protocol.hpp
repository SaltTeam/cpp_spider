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

#include <queue>
#include "Network/INetworkSession.hpp"
#include "Network/BoostNetworkSession.hpp"
#include "IProtocol.hpp"
#include "Serializer.hpp"

namespace spider
{
  class Protocol : public IProtocol
  {
  protected:
    std::queue<t_command>	cmds;
    INetworkSession		session;
    Serializer			serializer;

  public:
    Protocol();
    ~Protocol();

    void		sendData(t_message message);
    void		sendData(t_command cmd);
    void		sendData(t_register _register);
    void		sendData(t_mouse mouse);

    void		sendPing() override;
    bool		hasCommand() override;
    void		getCommand() override;
  };
}
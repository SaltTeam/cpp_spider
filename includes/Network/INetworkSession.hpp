/*
** INetwork.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/Network/INetwork.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Sep 28 12:07:44 2017 Maxime PILLON
** Last update Thu Sep 28 12:07:44 2017 Maxime PILLON
*/

#pragma once

/// \namespace spider
namespace spider
{
  /// \class INetworkSession
  class INetworkSession
  {
  public:
    /// \brief The destructor.
    virtual ~INetwork() {}

    virtual void setConnectCallback() = 0;

    virtual void setSendCallback() = 0;

    virtual void setRecvCallback() = 0;

    virtual void setAcceptCallback() = 0;

    virtual void Connect() = 0;

    virtual void Connect(unsigned int timeout) = 0;

    virtual void Send() = 0;

    virtual void Send(unsigned int timeout) = 0;

    virtual void Recv() = 0;

    virtual void Recv(unsigned int timeout) = 0;

    virtual void Accept() = 0;

    virtual void Accept(unsigned int timeout) = 0;

  };
}
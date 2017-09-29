/*
** INetwork.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/Network/INetwork.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Sep 28 12:07:44 2017 Maxime PILLON
** Last update Fri Sep 29 08:46:57 2017 Hugo SOSZYNSKI
*/

#pragma once

#undef SERVER_CERT
#define SERVER_CERT "resources/pki_tmp/server.crt"

#undef SERVER_KEY
#define SERVER_KEY "resources/pki_tmp/server.key"

#undef SERVER_PASSWD
#define SERVER_PASSWD "test_pem_password"

#undef CLIENT_CERT
#define CLIENT_CERT "resources/pki_tmp/server.crt"

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

    virtual void Send() = 0;

    virtual void Recv() = 0;

    virtual void Accept() = 0;

    virtual void Select() = 0;

  };
}
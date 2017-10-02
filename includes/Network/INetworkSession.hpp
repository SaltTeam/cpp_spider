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

#include <string>

/// \namespace spider
namespace spider
{
  /// \class INetworkSession
  class INetworkSession
  {
  public:
    /// \brief The destructor.
    virtual ~INetwork() {}

    template <typename ConnectHandler>
    virtual void Connect(ConnectHandler hdl) = 0;

    template <typename SendHandler>
    virtual void Send(std::string const& msg, SendHandler hdl) = 0;

    template <typename RecvHandler>
    virtual void Recv(RecvHandler hdl) = 0;

    template<typename AcceptHandler>
    virtual INetworkSession& Accept(AcceptHandler hdl) = 0;

    virtual void Select() = 0;

  };
}
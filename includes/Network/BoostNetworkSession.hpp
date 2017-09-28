/*
** Network.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/Network/Network.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Sep 28 12:09:55 2017 Maxime PILLON
** Last update Thu Sep 28 12:09:55 2017 Maxime PILLON
*/

#pragma once

#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "INetworkSession.hpp"

/// \namespace spider
namespace spider
{
  /// \class BoostNetworkSession
  class BoostNetworkSession: public INetworkSession
  {
  public :

    BoostNetworkSession(std::string const& host, std::string const& port);

    ~BoostNetworkSession();

  public:
    virtual void setConnectCallback();

    virtual void setSendCallback();

    virtual void setRecvCallback();

    virtual void setAcceptCallback();

    virtual void Connect();

    virtual void Connect(unsigned int timeout);

    virtual void Send();

    virtual void Send(unsigned int timeout);

    virtual void Recv();

    virtual void Recv(unsigned int timeout);

    virtual void Accept();

    virtual void Accept(unsigned int timeout);

  protected:
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _socket;
    boost::asio::ssl::context _context;
    boost::asio::io_service _ios;
    boost::asio::ip::tcp::acceptor _acceptor;
  };
}
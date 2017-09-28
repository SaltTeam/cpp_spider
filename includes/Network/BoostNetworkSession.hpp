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

using boost_ssl_socket = boost::asio::ssl::stream<boost::asio::ip::tcp::socket>;

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
    void setConnectCallback();

    void setSendCallback() override;

    void setRecvCallback() override;

    void setAcceptCallback() override;

    void Connect() override;

    void Connect(unsigned int timeout) override;

    void Send() override;

    void Send(unsigned int timeout) override;

    void Recv() override;

    void Recv(unsigned int timeout) override;

    void Accept() override;

    void Accept(unsigned int timeout) override;

  protected:
    boost_ssl_socket _socket;
    boost::asio::ssl::context _context;
    boost::asio::io_service _ios;
    boost::asio::ip::tcp::acceptor _acceptor;
  };
}
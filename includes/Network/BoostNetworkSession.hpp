/*
** Network.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/Network/Network.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Sep 28 12:09:55 2017 Maxime PILLON
** Last update Fri Sep 29 08:46:50 2017 Hugo SOSZYNSKI
*/

#pragma once

#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "INetworkSession.hpp"

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> boost_ssl_socket;

/// \namespace spider
namespace spider
{
  /// \class BoostNetworkSession
  class BoostNetworkSession: public INetworkSession
  {
  public :

    BoostNetworkSession(std::string const& host, unsigned short port);
    explicit BoostNetworkSession(unsigned short port);
    explicit BoostNetworkSession(std::unique_ptr<boost_ssl_socket>& socket);

    virtual ~BoostNetworkSession();

  public:

    template <typename ConnectHandler>
    void Connect(ConnectHandler hdl) override;

    template <typename SendHandler>
    void Send(std::string const& msg, SendHandler hdl) override;

    template <typename RecvHandler>
    void Recv(RecvHandler hdl) override;

    template<typename AcceptHandler>
    BoostNetworkSession& Accept(AcceptHandler hdl) override;

    void Select() override;

  protected:
    static std::string get_ssl_passwd() const;

  protected:
    std::string _host;
    unsigned short _port;
    std::unique_ptr<boost::asio::io_service> _ios;
    std::unique_ptr<boost::asio::ssl::context> _context;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> _acceptor;
    std::unique_ptr<boost_ssl_socket> _socket;
  };
}
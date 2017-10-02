/*
** BoostNetworkSession.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/Network/BoostNeworkSession.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Sep 28 12:58:49 2017 Maxime PILLON
** Last update Fri Sep 29 08:46:45 2017 Hugo SOSZYNSKI
*/

#include <boost/bind.hpp>
#include "Network/BoostNetworkSession.hpp"

spider::BoostNetworkSession::BoostNetworkSession(std::string const& host,
						 unsigned short port)
  : _host(host), _port(port)
{
  // Here, we are in client mode.

  _ios = new boost::asio::io_service();

  _context = new boost::asio::ssl::context(boost::asio::ssl::context::tlsv12);
  _context->load_verify_file(CLIENT_CERT);

  _socket = new boost_ssl_socket(*_ios, *_context);
  _socket->set_verify_mode(boost::asio::ssl::verify_peer);
}

spider::BoostNetworkSession::BoostNetworkSession(unsigned short port)
  : _host(), _port(port)
{
  _ios = new boost::asio::io_service();

  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
  _acceptor = new boost::asio::ip::tcp::acceptor(*_ios, endpoint);

  _context = new boost::asio::ssl::context(boost::asio::ssl::context::tlsv12);
  _context->set_options(boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::no_sslv3
        | boost::asio::ssl::context::single_dh_use);
  _context->set_password_callback(spider::BoostNetworkSession::get_ssl_passwd());
  _context->use_certificate_chain_file(SERVER_CERT);
  _context->use_private_key_file(SERVER_KEY);
}

spider::BoostNetworkSession::BoostNetworkSession(std::unique_ptr<boost_ssl_socket>& socket)
  : _host(), _port(0)
{
  _socket = std::move(socket);
}

spider::BoostNetworkSession::~BoostNetworkSession()
{

}

template <typename ConnectHandler>
void spider::BoostNetworkSession::Connect(ConnectHandler hdl)
{
  this->_socket->lowest_layer().async_connect(
    boost::asio::ip::tcp::endpoint(
      boost::asio::ip::address::from_string(this->_host),
      this->_port),
    hdl);
}

template <typename SendHandler>
void spider::BoostNetworkSession::Send(std::string const& msg, SendHandler hdl)
{

}

template <typename RecvHandler>
void spider::BoostNetworkSession::Recv(RecvHandler hdl)
{

}

template<typename AcceptHandler>
spider::BoostNetworkSession& spider::BoostNetworkSession::Accept(AcceptHandler hdl)
{
  std::unique_ptr<boost_ssl_socket> sock(new boost_ssl_socket(_ios, _context));
  _acceptor->async_accept(sock->lowest_layer(), hdl);
}

void spider::BoostNetworkSession::Select()
{

}

std::string spider::BoostNetworkSession::get_ssl_passwd() const
{
  return SERVER_PASSWD;
}
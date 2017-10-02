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

  _socket = new boost_ssl_socket(_ios, _context);
  _socket->set_verify_mode(boost::asio::ssl::verify_peer);
}

spider::BoostNetworkSession::BoostNetworkSession(unsigned short port)
  : _host(), _port(port)
{

}

spider::BoostNetworkSession::BoostNetworkSession(boost::asio::io_service& io_service,
boost::asio::ssl::context& context)
  : _host(), _port(0)
{

}

spider::BoostNetworkSession::~BoostNetworkSession()
{

}

void spider::BoostNetworkSession::setConnectCallback()
{

}

void spider::BoostNetworkSession::setSendCallback()
{

}

void spider::BoostNetworkSession::setRecvCallback()
{

}

void spider::BoostNetworkSession::setAcceptCallback()
{

}

void spider::BoostNetworkSession::Connect()
{

}

void spider::BoostNetworkSession::Send()
{

}

void spider::BoostNetworkSession::Recv()
{

}

void spider::BoostNetworkSession::Accept()
{

}

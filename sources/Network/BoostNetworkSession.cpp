/*
** BoostNeworkSession.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/Network/BoostNeworkSession.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Sep 28 12:58:49 2017 Maxime PILLON
** Last update Thu Sep 28 12:58:49 2017 Maxime PILLON
*/

#include <boost/bind.hpp>
#include "Network/BoostNetworkSession.hpp"

spider::BoostNetworkSession::BoostNetworkSession(std::string const& host,
						 unsigned short port)
  : _ios(), _context(boost::asio::ssl::context::tlsv12)
{
  // Here we are in client mode.

  _context.load_verify_file(SERVER_CERT);
  _socket = new boost_ssl_socket(_ios, _context);
  _socket->set_verify_mode(boost::asio::ssl::verify_peer);

}

spider::BoostNetworkSession::BoostNetworkSession(unsigned short port)
  : _ios(), _context(boost::asio::ssl::context::tlsv12)
{

}

spider::BoostNetworkSession::BoostNetworkSession(boost::asio::io_service& io_service,
boost::asio::ssl::context& context)
  : _ios(), _context(boost::asio::ssl::context::tlsv12)
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

void spider::BoostNetworkSession::Connect(unsigned int timeout)
{

}

void spider::BoostNetworkSession::Send()
{

}

void spider::BoostNetworkSession::Send(unsigned int timeout)
{

}

void spider::BoostNetworkSession::Recv()
{

}

void spider::BoostNetworkSession::Recv(unsigned int timeout)
{

}

void spider::BoostNetworkSession::Accept()
{

}

void spider::BoostNetworkSession::Accept(unsigned int timeout)
{

}
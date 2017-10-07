/*
** ClientNetwork.cpp for cpp_spider in /home/soszyn_h/rendu/cpp_spider/sources/Network/ClientNetwork.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Tue Oct 03 15:54:58 2017 Hugo SOSZYNSKI
** Last update Tue Oct 03 15:54:58 2017 Hugo SOSZYNSKI
*/

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Network/ClientNetwork.hpp"
#include "Protocol/Buffer.hpp"

spider::ClientNetwork::ClientNetwork(std::string const& host,
				     unsigned short port)
  : _ios(), _context(boost::asio::ssl::context::tlsv12),
    _endpoint(boost::asio::ip::address::from_string(host.c_str()), port),
    _connected(false)
{
  _light_buf[NET_BUFFER_LEN] = 0;
  _context.load_verify_file("resources/pki_tmp/server.crt");
}

spider::ClientNetwork::~ClientNetwork() = default;

void spider::ClientNetwork::connect()
{
  _socket.reset(new boost_ssl_socket(_ios, _context));
  _socket->set_verify_mode(boost::asio::ssl::verify_peer |
			   boost::asio::ssl::verify_fail_if_no_peer_cert);
  _socket->lowest_layer().async_connect(
    _endpoint,
    boost::bind(
      &ClientNetwork::handleConnect,
      this,
      boost::asio::placeholders::error
    )
  );
//  boost::asio::async_connect(_socket->lowest_layer(),
//			     _endpoint,
//			     boost::bind(&ClientNetwork::handleConnect,
//					 this,
//					 boost::asio::placeholders::error));
}

void spider::ClientNetwork::send(std::string const& msg)
{
  boost::asio::write(*_socket, boost::asio::buffer(msg.c_str(), msg.size()));
}

void spider::ClientNetwork::handleConnect(const boost::system::error_code& error)
{
  if (error)
  {
    _socket.release();
    _connected = false;
    return ;
  }
  _socket->async_handshake(boost::asio::ssl::stream_base::client,
			   boost::bind(&ClientNetwork::handleHandshake, this,
				       boost::asio::placeholders::error));
}

void spider::ClientNetwork::handleHandshake(const boost::system::error_code& error)
{
  if (error)
  {
    _socket.release();
    _connected = false;
    return ;
  }
  boost::asio::async_read(*_socket,
			  boost::asio::buffer(_light_buf, NET_BUFFER_LEN),
			  boost::bind(&ClientNetwork::handleRead,
				      this,
				      boost::asio::placeholders::error,
				      boost::asio::placeholders::bytes_transferred));
}

void spider::ClientNetwork::handleRead(const boost::system::error_code& error,
				       size_t bytes_transferred)
{
  if (error)
  {
    _socket.release();
    _connected = false;
    return ;
  }
  Buffer &buf = Buffer::BufferInstance();
  std::string str(_light_buf);
  str.resize(bytes_transferred);
  buf.push(str);
}

bool spider::ClientNetwork::isConnected() const
{
  return this->_connected;
}

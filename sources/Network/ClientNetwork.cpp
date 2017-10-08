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
#include <iostream>
#include <regex>
#include <Protocol/BufferSender.hpp>
#include "Network/ClientNetwork.hpp"
#include "Protocol/Buffer.hpp"

spider::ClientNetwork::ClientNetwork(std::string const& host,
				     unsigned short port)
  : _ios(), _context(boost::asio::ssl::context::tlsv12_client),
    _endpoint(boost::asio::ip::address::from_string(host.c_str()), port)
{
  _light_buf[NET_BUFFER_LEN] = 0;
  _context.load_verify_file("resources/cert/cert.pem");
}

spider::ClientNetwork::~ClientNetwork() = default;

void spider::ClientNetwork::connect()
{
  _socket.reset(new boost_ssl_socket(_ios, _context));
  _socket->set_verify_mode(boost::asio::ssl::verify_peer |
			   boost::asio::ssl::verify_fail_if_no_peer_cert);
  try
  {
    _socket->lowest_layer().connect(_endpoint);
    _socket->handshake(boost::asio::ssl::stream_base::client);
    isConnected.store(true);
  }
  catch (boost::system::system_error const& error)
  {
    _socket.release();
    isConnected.store(false);
  }
}

void spider::ClientNetwork::send()
{
  try
  {
    BufferSender &buf = BufferSender::BufferSenderInstance();

    std::string str = buf.getBuf();

    if (str.empty())
    {
      return ;
    }
    std::regex reg = std::regex("\\{(?:(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+\"data\": \\{(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+\\}(?:,{0}|,{1}(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+)|(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+)\\}");
    for (auto it = std::sregex_iterator(str.begin(), str.end(), reg);
	 it != std::sregex_iterator(); ++it)
    {
      _socket->write_some(boost::asio::buffer(str.c_str(), str.size()));
    }
  }
  catch (boost::system::system_error const& error)
  {
    _socket.release();
    isConnected.store(false);
  }
}

void spider::ClientNetwork::read()
{
  try
  {
    if (_socket->lowest_layer().available())
    {
      auto bytes_read = _socket->read_some(boost::asio::buffer(_light_buf, NET_BUFFER_LEN));
      Buffer& buf = Buffer::BufferInstance();
      buf.push(std::string().append(_light_buf, bytes_read));
    }
  }
  catch (boost::system::system_error const& error)
  {
    _socket.release();
    isConnected.store(false);
  }

}

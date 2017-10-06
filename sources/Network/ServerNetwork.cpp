/*
** ServerNetwork.cpp for cpp_spider in /home/soszyn_h/rendu/cpp_spider/sources/Network/ServerNetwork.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Wed Oct 04 08:04:50 2017 Hugo SOSZYNSKI
** Last update Wed Oct 04 08:04:50 2017 Hugo SOSZYNSKI
*/

#include <boost/bind.hpp>
#include "Protocol/Buffer.hpp"
#include "Network/ServerNetwork.hpp"

spider::ServerNetwork::ServerNetwork(unsigned short port)
  : _ios(), _context(boost::asio::ssl::context::tlsv12),
    _acceptor(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
  _context.set_options(
    boost::asio::ssl::context::default_workarounds
    | boost::asio::ssl::context::no_sslv2
    | boost::asio::ssl::context::single_dh_use);
  _context.set_password_callback(boost::bind(&ServerNetwork::get_password, this));
  _context.use_certificate_chain_file("server.crt");
  _context.use_private_key_file("server.key", boost::asio::ssl::context::pem);

  this->accept();
}

spider::ServerNetwork::~ServerNetwork() = default;


void spider::ServerNetwork::accept()
{
  NetworkSession* new_session = new NetworkSession(_ios, _context);
  _acceptor.async_accept(new_session->socket(),
			 boost::bind(&ServerNetwork::handleAccept,
				     this, new_session,
				     boost::asio::placeholders::error));
}

void spider::ServerNetwork::handleAccept(NetworkSession* session,
					 boost::system::error_code const& error)
{
  if (!error)
    session->start();
  else
    delete session;
  this->accept();
}

std::string spider::ServerNetwork::get_password() const
{
  return "test_pem_password";
}

spider::NetworkSession::NetworkSession(boost::asio::io_service& io_service,
				       boost::asio::ssl::context& context)
  : _socket(io_service, context)
{

}

spider::NetworkSession::~NetworkSession() = default;

void spider::NetworkSession::send(std::string const& msg)
{
  static_cast<void>(msg);
}

void spider::NetworkSession::start()
{
  _socket.async_handshake(
    boost::asio::ssl::stream_base::server,
    boost::bind(&NetworkSession::handleHandshake,
		this, boost::asio::placeholders::error)
  );
}

void
spider::NetworkSession::handleHandshake(boost::system::error_code const& error)
{
  if (!error)
  {
    _socket.async_read_some(
      boost::asio::buffer(_light_buf, NET_BUFFER_LEN),
      boost::bind(&NetworkSession::handleRead,
		  this, boost::asio::placeholders::error,
		  boost::asio::placeholders::bytes_transferred)
    );
  }
  else
    delete this;
}

void spider::NetworkSession::handleRead(boost::system::error_code const& error,
					std::size_t bytes_transferred)
{
  if (!error)
  {
    Buffer &buf = Buffer::BufferInstance();
    std::string str(_light_buf);
    str.resize(bytes_transferred);
    buf.push(str);
    _socket.async_read_some(
      boost::asio::buffer(_light_buf, NET_BUFFER_LEN),
      boost::bind(&NetworkSession::handleRead,
		  this, boost::asio::placeholders::error,
		  boost::asio::placeholders::bytes_transferred)
    );
  }
  else
    delete this;
}

boost_ssl_socket::lowest_layer_type& spider::NetworkSession::socket()
{
  return _socket.lowest_layer();
}

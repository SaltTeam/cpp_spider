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
#include <iostream>
#include "Protocol/ServerBuffer.hpp"
#include "Network/ServerNetwork.hpp"
#include "logger/Logger.hpp"

spider::ServerNetwork::ServerNetwork(unsigned short port)
  : _ios(), _context(boost::asio::ssl::context::tlsv12_server),
    _acceptor(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
  logger::Logger& logger = logger::Logger::getLogger();

  logger.log(logger::INFO, "Starting server network handling...");
  _context.set_options(
    boost::asio::ssl::context::default_workarounds
    | boost::asio::ssl::context::no_sslv2
    | boost::asio::ssl::context::single_dh_use);
  _context.set_password_callback(boost::bind(&ServerNetwork::get_password, this));
  _context.use_certificate_chain_file("resources/cert/cert.pem");
  _context.use_private_key_file("resources/cert/key.pem",
				boost::asio::ssl::context::pem);
  _context.use_tmp_dh_file("resources/cert/dHParam.pem");

  this->accept();
}

spider::ServerNetwork::~ServerNetwork() = default;


void spider::ServerNetwork::accept()
{
  logger::Logger& logger = logger::Logger::getLogger();

  logger.log(logger::DEBUG, "Accepting...");
  _new_session = new NetworkSession(_ios, _context);
  _acceptor.async_accept(_new_session->socket(),
			 boost::bind(&ServerNetwork::handleAccept,
				     this, boost::asio::placeholders::error));
}

void spider::ServerNetwork::handleAccept(boost::system::error_code const& error)
{
  logger::Logger& logger = logger::Logger::getLogger();

  if (!error)
  {
    logger.log(logger::INFO, "Accepted new connection.");
    _new_session->start();
  }
  else
  {
    logger.log(logger::ERROR, "Cannot accept connection: " + error.message());
    delete _new_session;
  }
  this->accept();
}

std::string spider::ServerNetwork::get_password() const
{
  return "toto";
}

void spider::ServerNetwork::run()
{
  std::cout << "BITE"<< std::endl;
  _ios.run();
  std::cout << "BOOBIES"<< std::endl;
}

spider::NetworkSession::NetworkSession(boost::asio::io_service& io_service,
				       boost::asio::ssl::context& context)
  : _socket(io_service, context)
{
  logger::Logger& logger = logger::Logger::getLogger();
  spider::ServerBuffer& buf = spider::ServerBuffer::ServerBufferInstance();

  logger.log(logger::DEBUG, "Creating new session");
  buf.registerSession(this);
}

spider::NetworkSession::~NetworkSession()
{
  logger::Logger& logger = logger::Logger::getLogger();
  spider::ServerBuffer& buf = spider::ServerBuffer::ServerBufferInstance();

  logger.log(logger::DEBUG, "Deleting session");
  buf.unregisterSession(this);
}

void spider::NetworkSession::send(std::string const& msg)
{
  static_cast<void>(msg);
}

void spider::NetworkSession::start()
{
  logger::Logger& logger = logger::Logger::getLogger();

  logger.log(logger::INFO, "Trying ssl handshake with client...");
  _socket.async_handshake(
    boost::asio::ssl::stream_base::server,
    boost::bind(&NetworkSession::handleHandshake,
		this, boost::asio::placeholders::error)
  );
}

void
spider::NetworkSession::handleHandshake(boost::system::error_code const& error)
{
  logger::Logger& logger = logger::Logger::getLogger();

  if (!error)
  {
    logger.log(logger::INFO, "SSL handshake successful.");
    _socket.async_read_some(
      boost::asio::buffer(_light_buf, NET_BUFFER_LEN),
      boost::bind(&NetworkSession::handleRead,
		  this, boost::asio::placeholders::error,
		  boost::asio::placeholders::bytes_transferred)
    );
  }
  else
  {
    logger.log(logger::ERROR, "SSL handshake failed: " + error.message());
    delete this;
  }
}

void spider::NetworkSession::handleRead(boost::system::error_code const& error,
					std::size_t bytes_transferred)
{
  logger::Logger& logger = logger::Logger::getLogger();

  if (!error)
  {
    logger.log(logger::DEBUG, "Reading data.");
    std::clog.write(_light_buf, bytes_transferred);
    std::clog << std::endl;
    std::string str(_light_buf);
    str.resize(bytes_transferred);
    ServerBuffer &buf = ServerBuffer::ServerBufferInstance();
    buf.push(this, str);
    _socket.async_read_some(
      boost::asio::buffer(_light_buf, NET_BUFFER_LEN),
      boost::bind(&NetworkSession::handleRead,
		  this, boost::asio::placeholders::error,
		  boost::asio::placeholders::bytes_transferred)
    );
  }
  else
  {
    logger.log(logger::DEBUG, "Cannot read data: " + error.message());
    delete this;
  }
}

boost_ssl_socket::lowest_layer_type& spider::NetworkSession::socket()
{
  return _socket.lowest_layer();
}

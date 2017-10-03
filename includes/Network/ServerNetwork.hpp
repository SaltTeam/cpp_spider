/*
** ServerNetwork.hpp for cpp_spider in /home/soszyn_h/rendu/cpp_spider/includes/Network/ServerNetwork.hpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Tue Oct 03 20:09:55 2017 Hugo SOSZYNSKI
** Last update Tue Oct 03 20:09:55 2017 Hugo SOSZYNSKI
*/

#ifndef CPP_SPIDER_SERVERNETWORK_HPP
# define CPP_SPIDER_SERVERNETWORK_HPP

# include <string>
# include <boost/asio.hpp>
# include <boost/asio/ssl.hpp>

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> boost_ssl_socket;

# undef NET_BUFFER_LEN
# define NET_BUFFER_LEN 1024

namespace spider
{
  class NetworkSession
  {
  public:
    NetworkSession(boost::asio::io_service& io_service, boost::asio::ssl::context& context);

    ~NetworkSession();

    NetworkSession(NetworkSession const&) = delete;

    NetworkSession& operator=(NetworkSession const&) = delete;

  public:
    void send(std::string const& msg);

    void start();

    void handleHandshake(boost::system::error_code const& error);

    void handleRead(boost::system::error_code const& error,
		    std::size_t bytes_transferred);

    boost_ssl_socket::lowest_layer_type& socket();

  private:
    boost_ssl_socket _socket;
    char _light_buf[NET_BUFFER_LEN];
  };

  class ServerNetwork
  {
  public:
    ServerNetwork(unsigned short port);

    ~ServerNetwork();

    ServerNetwork(ServerNetwork const&) = delete;

    ServerNetwork& operator=(ServerNetwork const&) = delete;

  public:
    void accept();

    void acceptHandler(boost::system::error_code const& error);

  private:
    boost::asio::io_service _ios;
    boost::asio::ssl::context _context;
    boost::asio::ip::tcp::acceptor _acceptor;

  };
}

#endif /* !CPP_SPIDER_SERVERNETWORK_HPP */

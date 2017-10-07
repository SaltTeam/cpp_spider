/*
** ClientNetwork.hpp for cpp_spider in /home/soszyn_h/rendu/cpp_spider/includes/Network/ClientNetwork.hpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Tue Oct 03 14:17:29 2017 Hugo SOSZYNSKI
** Last update Tue Oct 03 14:17:29 2017 Hugo SOSZYNSKI
*/

#ifndef CPP_SPIDER_CLIENTNETWORK_HPP
# define CPP_SPIDER_CLIENTNETWORK_HPP

# include <string>
# include <boost/asio.hpp>
# include <boost/asio/ssl.hpp>

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> boost_ssl_socket;

# undef NET_BUFFER_LEN
# define NET_BUFFER_LEN 1024

namespace spider
{
  class ClientNetwork
  {
  public:
    ClientNetwork(std::string const& host, unsigned short port);

    ~ClientNetwork();

    ClientNetwork(ClientNetwork const&) = delete;

    ClientNetwork& operator=(ClientNetwork const&) = delete;

  public:
    void connect();

    void send(std::string const& msg);

    bool isConnected() const;

    void handleConnect(const boost::system::error_code& error);

    void handleHandshake(const boost::system::error_code& error);

    void handleRead(const boost::system::error_code& error,
		    size_t bytes_transferred);
    void run();

    static void noop(boost::system::error_code const& e, std::size_t s) { static_cast<void>(e); static_cast<void>(s); }

  private:
    boost::asio::io_service _ios;
    boost::asio::ssl::context _context;
    boost::asio::ip::tcp::endpoint _endpoint;
    bool _connected;
    std::unique_ptr<boost_ssl_socket> _socket;
    char _light_buf[NET_BUFFER_LEN + 1];
  };
}
#endif /* !CPP_SPIDER_CLIENTNETWORK_HPP */

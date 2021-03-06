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

extern std::atomic_bool isConnected;

# undef NET_BUFFER_LEN
# define NET_BUFFER_LEN 1024

/// \namespace spider
namespace spider
{
  /// \class ClientNetwork
  class ClientNetwork
  {
  public:
    /// \brief The constructor.
    /// \param host The host to connect to.
    /// \param port The port to connect to.
    ClientNetwork(std::string const& host, unsigned short port);

    /// \brief The destructor.
    ~ClientNetwork();

    ClientNetwork(ClientNetwork const&) = delete;

    ClientNetwork& operator=(ClientNetwork const&) = delete;

  public:
    /// \brief Sync connect to distant host.
    void connect();

    /// \brief Send the data to distant host.
    void send();

    /// \brief Read data from distant host.
    void read();

  private:
    boost::asio::io_service _ios;
    boost::asio::ssl::context _context;
    boost::asio::ip::tcp::endpoint _endpoint;
    std::unique_ptr<boost_ssl_socket> _socket;
    char _light_buf[NET_BUFFER_LEN + 1];
  };
}
#endif /* !CPP_SPIDER_CLIENTNETWORK_HPP */

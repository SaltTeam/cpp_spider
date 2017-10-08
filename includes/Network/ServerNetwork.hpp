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

/// \namespace spider
namespace spider
{
  /// \class NetworkSession
  class NetworkSession
  {
  public:
    /// \brief Constructor.
    /// \param io_service The associated io_service.
    /// \param context The associated SSL context.
    NetworkSession(boost::asio::io_service& io_service, boost::asio::ssl::context& context);

    /// \brief The destructor.
    ~NetworkSession();

    NetworkSession(NetworkSession const&) = delete;

    NetworkSession& operator=(NetworkSession const&) = delete;

  public:

    /// \brief Starting the session.
    void start();

    /// \brief Handler for async ssl handshake.
    /// \param error The boost error code.
    void handleHandshake(boost::system::error_code const& error);

    /// \brief Handler for async read.
    /// \param error The boost error code.
    void handleRead(boost::system::error_code const& error,
		    std::size_t bytes_transferred);

    /// \brief Get the ip::tcp::socket.
    /// \return Ref to the ip::tcp::socket.
    boost_ssl_socket::lowest_layer_type& socket();

  private:
    boost_ssl_socket _socket;
    char _light_buf[NET_BUFFER_LEN];
  };

  /// \class ServerNetwork
  class ServerNetwork
  {
  public:
    /// \brief The constructor.
    /// \param port The port to bind to.
    ServerNetwork(unsigned short port);

    /// \brief The destructor.
    ~ServerNetwork();

    ServerNetwork(ServerNetwork const&) = delete;

    ServerNetwork& operator=(ServerNetwork const&) = delete;

  public:
    /// \brief Start accepting connections.
    void accept();

    /// \brief Handler for async accept.
    /// \param error The boost error code.
    void handleAccept(boost::system::error_code const& error);

    /// \brief Get the password for the pem key.
    /// \return The string containing the password.
    std::string get_password() const;

    /// \brief Run he pending handlers.
    void run();

  private:
    boost::asio::io_service _ios;
    boost::asio::ssl::context _context;
    boost::asio::ip::tcp::acceptor _acceptor;
    NetworkSession* _new_session;

  };
}

#endif /* !CPP_SPIDER_SERVERNETWORK_HPP */

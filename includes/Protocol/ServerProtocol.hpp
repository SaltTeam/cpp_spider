/*
** Protocol.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/Protocol/Protocol.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Sep 27 13:29:22 2017 Maxime PILLON
** Last update Wed Sep 27 13:29:22 2017 Maxime PILLON
*/

#pragma once

#include <queue>
#include "Network/ServerNetwork.hpp"
#include "IProtocol.hpp"
#include "Serializer.hpp"

# undef PORT
# define PORT 42000

/// \namespace spider
namespace spider
{
  /// \brief function that is passed in parameter of a thread
  void runServerNetwork();

  /// \brief function that is passed in parameter of a thread = 0 cause client side function
  void runNetwork();

  /// \class ServerProtocol
  class ServerProtocol : public IProtocol
  {
  protected:
    typedef std::queue<t_unserialized> unserialized_queue;

    std::queue<t_command>	cmds;
    unserialized_queue		data;

  public:
    /// \brief construct server protocol object
    ServerProtocol();

    /// \brief destruct of server protocol object
    ~ServerProtocol();

    /// \brief copy operator of server protocol
    ServerProtocol(ServerProtocol const &);

    /// \brief run the main function of the protocol
    void		run() override;

    /// \brief get the data which's waiting to be stock in DB
    ///
    /// \return the queue to be save in DB
    unserialized_queue& getInfo();

    /// \brief check if a ping command has been sent and respond to it
    void		checkPing() override;
  };
}
/*
** ClientProtocol.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/Protocol/ClientProtocol.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Oct 05 11:40:15 2017 Maxime PILLON
** Last update Thu Oct 05 11:40:15 2017 Maxime PILLON
*/

#pragma once

#include "queue"
#include "Network/ClientNetwork.hpp"
#include "IProtocol.hpp"
#include "Serializer.hpp"

# undef PORT
# define PORT 42000

extern std::atomic_bool isConnected;

/// \namespace spider
namespace spider
{
  /// \class ClientProtocol
  class ClientProtocol : public IProtocol
  {
  public:
    /// \brief construct client protocol object
    ClientProtocol();

    /// \brief destruct of client protocol object
    ~ClientProtocol() override;

  public:

    /// \brief check if a ping command has been sent and respond to it
    void checkPing() override;

    /// \brief run the main function of the protocol
    void run() override;
  };

  /// \brief function that is passed in parameter of a thread
  void runNetwork();

  /// \brief function that is passed in parameter of a thread = 0 cause server side function
  void runServerNetwork();
}
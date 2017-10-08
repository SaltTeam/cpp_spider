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

namespace spider
{
  class ClientProtocol : public IProtocol
  {
  public:
    ClientProtocol();
    ~ClientProtocol();

  public:
    void sendData() override;
    void sendPing() override;
    void run() override;
  };

  void runNetwork();

  void runServerNetwork();
}
/*
** Protocol.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/Protocol/Protocol.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Mon Oct 02 08:48:15 2017 Maxime PILLON
** Last update Mon Oct 02 08:48:15 2017 Maxime PILLON
*/

#include "Protocol/Buffer.hpp"
#include "Protocol/ServerProtocol.hpp"
#include <regex>

spider::ServerProtocol::ServerProtocol()
{
}

spider::ServerProtocol::~ServerProtocol() {}

spider::ServerProtocol::ServerProtocol(spider::ServerProtocol const &other)
{
  static_cast<void>(other);
}

void spider::ServerProtocol::checkPing() {}


spider::ServerProtocol::unserialized_queue &spider::ServerProtocol::getInfo()
{
  return data;
}

void spider::runServerNetwork()
{
  spider::ServerNetwork		net(PORT);

  net.run();
}

void spider::runNetwork() {};

void spider::ServerProtocol::run()
{
  Buffer &buf = Buffer::BufferInstance();
  std::string &str = buf.getBuf();
  std::regex reg = std::regex("\\{(?:(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+\"data\": \\{(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+\\}(?:,{0}|,{1}(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+)|(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+)\\}");

  for (auto it = std::sregex_iterator(str.begin(), str.end(), reg);
       it != std::sregex_iterator(); ++it)
  {
    this->data.push(Serializer::getSerializer().unserialize(Serializer::getSerializer().get_ptree_from_string(it->str())));
  }
}
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

spider::ServerProtocol::ServerProtocol() : net(PORT)
{
}

spider::ServerProtocol::~ServerProtocol() {}

spider::ServerProtocol::ServerProtocol(spider::ServerProtocol const &other) : net(PORT)
{
  static_cast<void>(other);
}

void spider::ServerProtocol::sendData(t_message message)
{
  Serializer::getSerializer().get_string_from_ptree(Serializer::getSerializer().serialize(message));
  //todo send this data;
}

void spider::ServerProtocol::sendData(t_command cmd)
{
  Serializer::getSerializer().get_string_from_ptree(Serializer::getSerializer().serialize(cmd));
  //todo send this data;
}

void spider::ServerProtocol::sendData(t_register _register)
{
  Serializer::getSerializer().get_string_from_ptree(
    Serializer::getSerializer().serialize(_register));
  //todo send this data;
}

void spider::ServerProtocol::sendData(t_mouse mouse)
{
  Serializer::getSerializer().get_string_from_ptree(Serializer::getSerializer().serialize(mouse));
  //todo send this data;
}

void spider::ServerProtocol::sendPing() {}

bool spider::ServerProtocol::hasCommand()
{
  return (false);
}

void spider::ServerProtocol::getCommand() {}

bool spider::ServerProtocol::connect() {}

spider::ServerProtocol::unserialized_queue &spider::ServerProtocol::getInfo()
{
  return data;
}

void spider::ServerProtocol::run()
{
  Buffer &buf = Buffer::BufferInstance();
  std::string &str = buf.getBuf();
  std::regex reg = std::regex("\\{(?:(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+\"data\": \\{(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+\\}(?:,{0}|,{1}(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+)|(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+)\\}");

  net.run();
  for (auto it = std::sregex_iterator(str.begin(), str.end(), reg);
       it != std::sregex_iterator(); ++it)
    this->data.push(Serializer::getSerializer().unserialize(Serializer::getSerializer().get_ptree_from_string(it->str())));
}
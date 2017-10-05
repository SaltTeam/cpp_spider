/*
** ClientProtocol.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/Protocol/ClientProtocol.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Oct 05 11:45:58 2017 Maxime PILLON
** Last update Thu Oct 05 11:45:58 2017 Maxime PILLON
*/

#include <regex>
#include "Protocol/Buffer.hpp"
#include "Protocol/ClientProtocol.hpp"


spider::ClientProtocol::ClientProtocol(std::string const &host,
				       unsigned short port) : _net(host, port)
{}

spider::ClientProtocol::~ClientProtocol()
{}

void spider::ClientProtocol::sendPing()
{}

spider::ClientProtocol::sendData()
{}

void spider::ClientProtocol::run()
{
  if (!_net.isConnected())
    return ;

  Buffer &buf = Buffer::BufferInstance();
  std::string &str = buf.getBuf();
  std::regex reg = std::regex("\\{(?:(?:\\s*\"\\w+\": \"\\w+\",{0,1}\\s*)+\"data\": \\{(?:\\s*\"\\w+\": \"\\w+\",{0,1}\\s*)+\\}(?:,{0}|,{1}(?:\\s*\"\\w+\": \"\\w+\",{0,1}\\s*)+)|(?:\\s*\"\\w+\": \"\\w+\",{0,1}\\s*)+)\\}");

  for (auto it = std::sregex_iterator(str.begin(), str.end(), reg);
       it != std::sregex_iterator(); ++it)
    _net.send(it->str());
}
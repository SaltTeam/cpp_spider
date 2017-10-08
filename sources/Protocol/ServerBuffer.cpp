/*
** ServerBuffer.cpp for cpp_spider in /home/soszyn_h/rendu/cpp_spider/sources/Protocol/ServerBuffer.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Fri Oct 06 16:45:54 2017 Hugo SOSZYNSKI
** Last update Fri Oct 06 16:45:54 2017 Hugo SOSZYNSKI
*/

#include <string>
#include "logger/Logger.hpp"
#include "Protocol/ServerBuffer.hpp"

namespace spider
{

  ServerBuffer ServerBuffer::_Instance = ServerBuffer();

  ServerBuffer::ServerBuffer()
  {

  }

  ServerBuffer::~ServerBuffer()
  {

  }

  void ServerBuffer::push(spider::NetworkSession* id, std::string msg)
  {
    logger::Logger& logger = logger::Logger::getLogger();

    logger.log(logger::DEBUG, "Pushing data on buffer");
    _buffer[id] += msg;
  }

  ServerBuffer& ServerBuffer::ServerBufferInstance()
  {
    return ServerBuffer::_Instance;
  }

  std::string ServerBuffer::getBuf(spider::NetworkSession* id)
  {
    std::string cpy(_buffer[id]);
    _buffer[id].clear();
    return (cpy);
  }

  void ServerBuffer::registerSession(spider::NetworkSession* id)
  {
    _buffer[id] = "";
  }

  void ServerBuffer::unregisterSession(spider::NetworkSession* id)
  {
    _buffer.erase(id);
  }
}
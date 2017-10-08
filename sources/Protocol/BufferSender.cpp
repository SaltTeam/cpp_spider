/*
** BufferSender.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/Protocol/BufferSender.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Sat Oct 07 18:38:52 2017 Maxime PILLON
** Last update Sat Oct 07 18:38:52 2017 Maxime PILLON
*/

#include <string>
#include "logger/Logger.hpp"
#include "Protocol/BufferSender.hpp"

namespace spider {

  BufferSender BufferSender::_Instance = BufferSender();

  BufferSender::BufferSender() : _buffer(std::string(""))
  {}

  BufferSender::~BufferSender() {

  }

  void BufferSender::push(std::string msg)
  {

    if (msg.empty())
      return ;
    this->mtx.lock();
    this->_buffer += msg;
    this->mtx.unlock();
  }
  BufferSender &BufferSender::BufferSenderInstance()
  {
    return BufferSender::_Instance;
  }

  std::string BufferSender::getBuf()
  {
    std::string	str;

    this->mtx.lock();
    str = this->_buffer;
    this->_buffer.clear();
    this->mtx.unlock();
    return (str);
  }
}
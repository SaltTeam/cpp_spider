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

  void BufferSender::push(std::string msg) {
    logger::Logger	&logger  = logger::Logger::getLogger();

    logger.log(logger::DEBUG, "Pushing data on bufferSender");
    this->mtx.lock();
    this->_buffer += msg;
    this->mtx.unlock();
  }

  BufferSender &BufferSender::BufferSenderInstance() {
    return BufferSender::_Instance;
  }

  const std::string &BufferSender::getBuf()
  {
    this->_tmp.clear();
    this->mtx.lock();
    this->_tmp = std::string(this->_buffer);
    this->_buffer.clear();
    this->mtx.unlock();
    std::cout << this->_tmp << std::endl;
    return (this->_tmp);
  }
}
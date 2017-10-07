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

  BufferSender::BufferSender() {

  }

  BufferSender::~BufferSender() {

  }

  void BufferSender::push(std::string msg) {
    logger::Logger	&logger  = logger::Logger::getLogger();

    logger.log(logger::DEBUG, "Pushing data on bufferSender");
    this->_buffer.store(this->_buffer.load() + msg);
  }

  BufferSender &BufferSender::BufferSenderInstance() {
    return BufferSender::_Instance;
  }

  std::string& BufferSender::getBuf() { return (_buffer); }
}
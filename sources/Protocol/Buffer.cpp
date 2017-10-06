/*
** Buffer.cpp for cpp_spider in /home/soszyn_h/rendu/cpp_spider/sources/Protocol/Buffer.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Fri Oct 06 16:45:54 2017 Hugo SOSZYNSKI
** Last update Fri Oct 06 16:45:54 2017 Hugo SOSZYNSKI
*/

#include <string>
#include "Protocol/Buffer.hpp"

namespace spider {

  Buffer Buffer::_Instance = Buffer();

  Buffer::Buffer() {

  }

  Buffer::~Buffer() {

  }

  void Buffer::push(std::string msg) {
    this->_buffer += msg;
  }

  Buffer &Buffer::BufferInstance() {
    return Buffer::_Instance;
  }

  std::string& Buffer::getBuf() { return (_buffer); }
}
/*
** BufferSender.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/Protocol/BufferSender.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Sat Oct 07 18:39:30 2017 Maxime PILLON
** Last update Sat Oct 07 18:39:30 2017 Maxime PILLON
*/

#pragma once

#include <string>
#include <map>
#include <boost/atomic/atomic.hpp>

/// \namespace spider
namespace spider {

  /// \class Buffer
  class BufferSender {
  public:
    /// \brief constructor
    BufferSender();

    /// \brief destructor
    ~BufferSender();

    /// \brief deleted copy constructor
    BufferSender(BufferSender const &copy){static_cast<void>(copy);}

    /// \brief deleted operator =
    BufferSender& operator=(BufferSender const& copy){ static_cast<void>(copy); return *this; }

  public:
    /// \brief Call a BufferSender Instance
    /// \return instance of BufferSender class
    static BufferSender &BufferSenderInstance();

    std::string& getBuf();

    /// \brief push a string in the buffer
    void push(std::string msg);

  private:
    static BufferSender _Instance;
    boost::atomic<std::string> _buffer;
  };
}
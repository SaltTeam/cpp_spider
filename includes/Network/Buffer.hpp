/*
** Buffer.hpp for cpp_spider in /home/soszyn_h/rendu/cpp_spider/includes/Network/Buffer.hpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Tue Oct 03 20:16:37 2017 Hugo SOSZYNSKI
** Last update Tue Oct 03 20:16:37 2017 Hugo SOSZYNSKI
*/

#ifndef _BUFFER_HPP
# define _BUFFER_HPP

#include <string>

/// \namespace spider
namespace spider
{

  /// \class Buffer
  class Buffer
  {
  private:
    /// \brief constructor
    Buffer();

    /// \brief destructor
    ~Buffer();

    /// \brief deleted copy constructor
    Buffer(Buffer const &copy) = delete;

    /// \brief deleted operator =
    Buffer *operator=(Buffer const &copy) = delete;

  public:
    /// \brief Call a Buffer Instance
    static Buffer &BufferInstance();

    /// \brief push a string in the buffer
    void push(std::string msg);

    std::string& getBuf();

  private:
    static Buffer _Instance;
    std::string _buffer;
  };
}

#endif //_BUFFER_HPP

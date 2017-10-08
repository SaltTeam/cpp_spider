/*
** ServerBuffer.hpp for cpp_spider in /home/soszyn_h/rendu/cpp_spider/includes/Network/ServerBuffer.hpp
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
#include <map>
#include "Network/ServerNetwork.hpp"

/// \namespace spider
namespace spider {

  /// \class ServerBuffer
  class ServerBuffer {
  public:
    /// \brief constructor
    ServerBuffer();

    /// \brief destructor
    ~ServerBuffer();

    /// \brief copy constructor
    ServerBuffer(ServerBuffer const &copy){ static_cast<void>(copy); }

    /// \brief operator =
    ServerBuffer& operator=(ServerBuffer const& copy){ static_cast<void>(copy); return *this; }

  public:
    /// \brief Call a ServerBuffer Instance
    /// \return instance of ServerBuffer class
    static ServerBuffer &ServerBufferInstance();

    /// \brief Get the current buffer content and empty it.
    /// \param id The session id.
    /// \return A copy of the buffer content.
    std::string getBuf(spider::NetworkSession* id);

    /// \brief push a string in the buffer.
    /// \param id The id of the session.
    /// \param msg The data to push in the buffer.
    void push(spider::NetworkSession* id, std::string msg);

    /// \brief Register the session in the buffer.
    /// \param id The session id to be registered.
    void registerSession(spider::NetworkSession* id);

    /// \brief Unregister the session in the buffer.
    /// \param id The session id to be unregistered.
    void unregisterSession(spider::NetworkSession* id);

  private:
    static ServerBuffer _Instance;

    std::map<spider::NetworkSession*, std::string> _buffer;
  };
}

#endif //_BUFFER_HPP
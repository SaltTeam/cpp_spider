/*
** core.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/core.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Fri Sep 29 07:58:37 2017 Maxime PILLON
** Last update Fri Sep 29 07:58:37 2017 Maxime PILLON
*/

#pragma once

# include "Database/Sqlite.hpp"
# include "Protocol/ServerProtocol.hpp"

/// \namespace spider
namespace spider
{
  /// \class ServerCore
  class ServerCore
  {
  protected:

      /// \brief database
    Sqlite			_db;

      /// \ brief communication protocol class
    ServerProtocol		_proto;

  public:
      /// \brief default constructor
      ServerCore();

      /// \brief default destructor
      virtual  ~ServerCore();

      /// \brief run server
    void run();
  };
}
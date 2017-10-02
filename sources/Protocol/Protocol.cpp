/*
** Protocol.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/Protocol/Protocol.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Mon Oct 02 08:48:15 2017 Maxime PILLON
** Last update Mon Oct 02 08:48:15 2017 Maxime PILLON
*/

#include "Protocol/Protocol.hpp"

spider::Protocol::Protocol()
{

}

spider::Protocol::~Protocol()
{

}

void spider::Protocol::sendData(t_message message)
{
  this->serializer.get_string_from_ptree(this->serializer.serialize(message));
  //todo send this data;
}

void spider::Protocol::sendData(t_command cmd)
{
  this->serializer.get_string_from_ptree(this->serializer.serialize(cmd));
  //todo send this data;
}

void spider::Protocol::sendData(t_register _register)
{
  this->serializer.get_string_from_ptree(this->serializer.serialize(_register));
  //todo send this data;
}

void spider::Protocol::sendData(t_mouse mouse)
{
  this->serializer.get_string_from_ptree(this->serializer.serialize(mouse));
  //todo send this data;
}

void spider::Protocol::sendPing()
{
}

bool spider::Protocol::hasCommand()
{
}

void spider::Protocol::getCommand()
{
}


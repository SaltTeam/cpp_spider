/*
** Protocol.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/Protocol/Protocol.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Mon Oct 02 08:48:15 2017 Maxime PILLON
** Last update Mon Oct 02 08:48:15 2017 Maxime PILLON
*/

#include "Protocol/Buffer.hpp"
#include "Protocol/Protocol.hpp"
#include <regex>

spider::Protocol::Protocol() : net(PORT)
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

unserialized_queue& spider::Protocol::getInfo()
{
  return data;
}

void spider::Protocol::run()
{
	Buffer& buf = Buffer::BufferInstance();
	std::string& str = buf.getBuf();
	std::regex reg = std::regex("\\{(?:(?:\\s*\"\\w+\": \"\\w+\",{0,1}\\s*)+\"data\": \\{(?:\\s*\"\\w+\": \"\\w+\",{0,1}\\s*)+\\}(?:,{0}|,{1}(?:\\s*\"\\w+\": \"\\w+\",{0,1}\\s*)+)|(?:\\s*\"\\w+\": \"\\w+\",{0,1}\\s*)+)\\}");

	for (auto it = std::sregex_iterator(str.begin(), str.end(), reg); it != std::sregex_iterator(); ++it)
		this->data.push(this->serializer.unserialize(this->serializer.get_ptree_from_string(it->str())));
}
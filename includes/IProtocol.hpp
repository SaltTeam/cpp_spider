/*
** Protocol.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/Protocol.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Mon Sep 25 13:31:02 2017 Maxime PILLON
** Last update Mon Sep 25 13:31:02 2017 Maxime PILLON
*/

#ifndef IPROTOCOL_HPP_
# define IPROTOCOL_HPP_

enum class Transmission
{
  EOT = 0,
  PING,
  PONG,
  SEND,
  ASEND,
};

enum class Order
{
  //active
  //passive
};



#endif // !IPROTOCOL_HPP_
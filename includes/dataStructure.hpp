/*
** dataStructure.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/dataStructure.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Sep 27 14:49:22 2017 Maxime PILLON
** Last update Wed Sep 27 14:49:22 2017 Maxime PILLON
*/

#pragma once

# include <ctime>

struct		t_message {
  const char	*mac;
  const char 	*timestamp;
  const char	*process;
  const char	*message;
};

struct		t_register {
  const char	*os;
  const char	*mac;
  const char	*antivirus;
};
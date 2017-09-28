/*
** main.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/Database/main.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Sep 27 14:58:07 2017 Maxime PILLON
** Last update Wed Sep 27 14:58:07 2017 Maxime PILLON
*/

#include "Database/Sqlite.hpp"
#include "dataStructure.hpp"

int		main(int ac, char **av)
{
  spider::Sqlite db;

  db.open("test.sqlite");
  db.createDb();
  db.addEntryLog("123123131", "123131312313", "firefox", "maxime.pillon@epitech.eu");
  db.close();
}
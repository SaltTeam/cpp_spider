/*
** Sqlite.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/Sqlite.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Tue Sep 26 12:35:06 2017 Maxime PILLON
** Last update Tue Sep 26 12:35:06 2017 Maxime PILLON
*/

#ifndef SQLITE_HPP_
# define SQLITE_HPP_

# include <sqlite3.h>
# include "IDatabase.hpp"

/// \namespace spider
namespace spider
{
  class Sqlite : public IDatabase
  {
  protected:
    sqlite3		*_db;
    const char*		_data = "Callback function called";

  public:
    Sqlite();
    virtual ~Sqlite();

  protected:
    void execute(const char *querry);

    bool open(const char *filename);

    void close();
  };
}

#endif // !SQLITE_HPP_

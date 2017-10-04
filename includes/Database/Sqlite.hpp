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
#include <dataStructure.hpp>
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
    ~Sqlite() override;

    void execute(const char *querry) override;

    bool open(const char *filename) override;

    void createDb() override;

    void dropDb() override;

    void close() override;

    void pushData(t_unserialized data);

    void addEntryLog(const char *time, const char *proccess, const char *message);

    void addEntryRegister(const char *mac, const char *os, const char *antivirus);

    void removeEntryRegister(int id);

    void removeEntryLog(int id) override;

    void treat(unserialized_queue &toTreat) override;
  };
}

#endif // !SQLITE_HPP_

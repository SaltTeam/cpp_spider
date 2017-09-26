/*
** Sqlite.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/Database/Sqlite.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Tue Sep 26 13:02:39 2017 Maxime PILLON
** Last update Tue Sep 26 13:02:39 2017 Maxime PILLON
*/

#include	<iostream>
#include	"Database/Sqlite.hpp"

static int	callback(void *data, int argc, char **argv, char **azColName)
{
  int		i;

  std::cerr << (const char *)data << std::endl;

  for(i = 0; i < argc; i++)
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  printf("\n");
  return (0);
}

spider::Sqlite::Sqlite() {}

spider::Sqlite::~Sqlite() {}

bool	spider::Sqlite::open(const char *filename)
{
  int	rc;

  rc = sqlite3_open(filename, &_db);
  if (rc)
  {
    std::cerr << "Can't open database: " << sqlite3_errmsg(_db) << std::endl;
    return false;
  }
  else
    return true;
}

void spider::Sqlite::close()
{
  sqlite3_close(_db);
}

void	spider::Sqlite::execute(const char *querry)
{
  int	rc;
  char *zErrMsg = nullptr;

  rc = sqlite3_exec(_db, querry, callback, (void*)_data, &zErrMsg);

  if( rc != SQLITE_OK ) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    fprintf(stdout, "Operation done successfully\n");
  }
}

void spider::Sqlite::addEntry(char *mac, char *time, char *proccess,
			      char *message)
{
  // create the querry then use execute
}

void spider::Sqlite::removeEntry(int id)
{
  // create the query the use execute
}
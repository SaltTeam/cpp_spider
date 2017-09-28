/*
** IDatabase.hpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/includes/IDatabase.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Tue Sep 26 11:54:43 2017 Maxime PILLON
** Last update Tue Sep 26 11:54:43 2017 Maxime PILLON
*/


#ifndef IDATABASE_HPP_
# define IDATABASE_HPP_

/// \namespace spider
namespace spider
{
  /// \class IDatabase
  class IDatabase
  {
  public:

    virtual ~IDatabase(void) {};

    /// \brief Initialise or create a database.
    ///
    /// \param filename, filename of the db
    /// \return True if the db is created or opened
    virtual bool open(const char *filename) = 0;

    /// \brief Execute an Querry to the database
    ///
    /// \param Querry the statement to execute
    virtual void execute(const char *Querry) = 0;

    /// \brief drop all the database row
    virtual void dropDb() = 0;

    /// \brief create all the tables if it's needed
    virtual void createDb() = 0;

    /// \brief Add a row to the database
    ///
    /// \param mac address mac
    /// \param time timestamp of the action
    /// \param proccess process where the commad has been typed
    /// \param message message which has been typed
    virtual void addEntryLog(const char *mac, const char *time, const char *proccess, const char *message) = 0;

    /// \brief Close the actual database
    virtual void close() = 0;
  };
}

#endif // !IDATABASE_HPP_

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

    /// \brief Close the actual database
    virtual void close() = 0;
  };
}

#endif // !IDATABASE_HPP_

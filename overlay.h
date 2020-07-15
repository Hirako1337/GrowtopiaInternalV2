#include <string>
#include <Windows.h>
#include <iostream>
void show(HWND hwnd)
{
    WINDOWPLACEMENT place = { sizeof(WINDOWPLACEMENT) };
    GetWindowPlacement(hwnd, &place);
    switch(place.showCmd)
    {
    case SW_SHOWMAXIMIZED:
        ShowWindow(hwnd, SW_SHOWMAXIMIZED);
        break;
    case SW_SHOWMINIMIZED:
        ShowWindow(hwnd, SW_RESTORE);
        break;
    default:
        ShowWindow(hwnd, SW_NORMAL);
        break;
    }
    SetWindowPos(0, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
    SetForegroundWindow(hwnd);
}
void initOverlay() {
	static char watermark[48] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n `sINTERNAL";
				DWORD oldProtect = 0;
				DWORD OLDPROTECT;
				int oldprot = 0;
				LPVOID entrys = (LPVOID)((uintptr_t)GetModuleHandle(NULL) + 0x43D210);
				HANDLE as = GetCurrentProcess();
				VirtualProtectEx(as, entrys, sizeof(watermark), PAGE_EXECUTE_READWRITE, &OLDPROTECT);
				memcpy(entrys, watermark, sizeof(watermark));
		HWND Growtopia = FindWindow(NULL, "Growtopia");
		show(Growtopia);
		show(Growtopia);
		show(Growtopia);
		INPUT ip;
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0;
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;


		// Press the "Ctrl" key
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		// Press the "V" key
		ip.ki.wVk = 'F';
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		// Release the "V" key
		ip.ki.wVk = 'F';
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		// Release the "Ctrl" key
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
}

void removeOverlay() {
	static char watermark[48] = "fps: %d - M: %.2f, T: %.2f A: %.2f F: %.2f";
				DWORD oldProtect = 0;
				DWORD OLDPROTECT;
				int oldprot = 0;
				LPVOID entrys = (LPVOID)((uintptr_t)GetModuleHandle(NULL) + 0x43D210);
				HANDLE as = GetCurrentProcess();
				VirtualProtectEx(as, entrys, sizeof(watermark), PAGE_EXECUTE_READWRITE, &OLDPROTECT);
				memcpy(entrys, watermark, sizeof(watermark));
		HWND Growtopia = FindWindow(NULL, "Growtopia");
		show(Growtopia);
		show(Growtopia);
		show(Growtopia);
		INPUT ip;
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0;
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;


		// Press the "Ctrl" key
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		// Press the "V" key
		ip.ki.wVk = 'F';
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		// Release the "V" key
		ip.ki.wVk = 'F';
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		// Release the "Ctrl" key
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
}

#include "includes.h"
#include "phook.h"
#include "overlay.h"
#include <string>
#include "utils.hpp"
#include "unbanner.h"
using namespace std;
HWND window;
void* pDevice[119];
PTR EndSceneAddress;
EndScene oEndScene;
WNDPROC oWndProc;
using namespace std;
uintptr_t* skinAddress;
uintptr_t mBase;
uintptr_t App;

int currentDropIt = 0;
int currentClothing = 0;

bool hasLogonAlready = false;

typedef uintptr_t func(...);
typedef void func2(int a1, string a2, uint64_t a3);

// sig scan soon, for now ill just constantly update these and perhaps bring out a full tutorial on how to find them, completely bringing out the internal out of gt children's mind existence.
#define Addr_LogToConsole 0x24FA00
#define Addr_GameVersion 0x9fb6f
#define Addr_SendPacket 0x2E20A0
#define Addr_SetFPSLimit 0x11060
#define Addr_GetApp 0x9E090
#define Addr_GetClient 0x9C6C0
#define Addr_SendPacketRaw 0x2E2120
#define Addr_LogWarningToConsole 0x26A3C0
#define Addr_RequestJoinWorldCommon 0x2B31C0
#define Addr_OnTextOverlay 0x1F3D40
#define Addr_OnChangeSkin 0x2D0340
#define Addr_OnConsoleMessage 0x1F7F90
#define Addr_ProcessTankUpdatePacket 0x1F5840
struct GameLogicComponent {

};

typedef uint64_t(__cdecl* _app)();
_app getapp2;
typedef void(__fastcall* _SendPackets)(int a1, string a2, uint64_t a3);
_SendPackets SendPacket;
typedef void(__fastcall* _SendPacketRaw)(int a1, void* data, int size, void* a4, uint64_t a5, int a6);
_SendPacketRaw SendPacketRaw;


func* LogToConsole;

typedef void(*Log)(char* text);
uintptr_t ltchook;
uintptr_t sphook;
uintptr_t sprhook;
uintptr_t ptuphook;

string gamever = "4.00";


uint64_t getpeer() {
	getapp2 = (_app)(mBase + Addr_GetApp);

	return *(uint64_t*)(*(uint64_t*)(getapp2() + 3984) + 200i64);
}
__int64 peery = 0;

//declares
#define NOP 0x90
//declares

void nop_(PVOID address, int bytes) {
	DWORD d, ds;
	VirtualProtect(address, bytes, PAGE_EXECUTE_READWRITE, &d);
	memset(address, NOP, bytes);
	VirtualProtect(address, bytes, d, &ds);
}




void SendPacketHook(int a1, string a2, uint64_t a3) {

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)sphook, &SendPacketHook);
	DetourTransactionCommit();


	

	SendPacket(a1, a2, a3);




	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)sphook, &SendPacketHook);
	DetourTransactionCommit();
}

struct TankPacketStruct
{
#pragma pack (push,1)
	byte packetType;
	byte padding1;
	short padding2;
	int NetID;
	int secondaryNetID;
	int characterState;
	float padding3;
	int value;
	float x, y;
	int XSpeed, YSpeed;
	int padding4;
	int punchX, punchY;
	int extDataSize = 0;
#pragma pack (pop)
};

byte* packTankStruct(TankPacketStruct* tPckt)
{
	byte* raw = (byte*)tPckt;
	return raw;
}

void InitImGui(LPDIRECT3DDEVICE9 device)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
}

bool initialized = false;
long __stdcall PHook::hkEndScene(LPDIRECT3DDEVICE9 device)
{
	if (!initialized)
	{
		InitImGui(device);
		initialized = true;
	}
	/*uintptr_t* addr1 = (uintptr_t*)(mBase + 0x574F08);
	uintptr_t* addr2 = (uintptr_t*)(*addr1 + 0x238);
	uintptr_t* addr3 = (uintptr_t*)(*addr2 + 0x80);
	uintptr_t* addr4 = (uintptr_t*)(*addr3 + 0x180);
	uintptr_t* addr5 = (uintptr_t*)(*addr4 + 0x0);
	uintptr_t* addr6 = (uintptr_t*)(*addr5 + 0x178);
	uintptr_t* addr7 = (uintptr_t*)(*addr6 + 0x1B0);
	skinAddress = (uintptr_t*)(*addr7 + 0x3D0);*/

	//cout << "Skin value is: " << *(int*)skinAddress << endl;

	/*ONLY CLIENT SIDED CALLS*/
	LogToConsole = (func*)(mBase + Addr_LogToConsole);
	func* SetFPSLimit = (func*)(mBase + Addr_SetFPSLimit);
	func* GetApp = (func*)(mBase + Addr_GetApp);

	func* OnConsoleMessage = (func*)(mBase + Addr_OnConsoleMessage);
	SendPacketRaw = (_SendPacketRaw)(mBase + Addr_SendPacketRaw);


	/*ONLY CLIENT SIDED CALLS*/
	SendPacket = (_SendPackets)(mBase + Addr_SendPacket);
	App = GetApp();

	/*CALLS WHERE SERVER COMMUNICATION IS INVOLVED*/
	void* peer = (void*)(mBase + (App + 3984) + 200i64);

	/*CALLS WHERE SERVER COMMUNICATION IS INVOLVED*/


	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	static bool no_move = false;
	static char show_pussy = 0;
	static bool no_background = false; static bool no_resize = true;
	ImGuiWindowFlags window_flags = 0;

	ImGui::Begin("Internal", NULL,ImGuiWindowFlags_NoCollapse);
	static char ip[20] = "growtopia1.com";
	static char port[10] = "17092";
	static char flags[10] = "lk";
	if (GetAsyncKeyState(VK_F6)) {
		ImVec2 lastpos;
		if (show_pussy == 1) {
			lastpos = ImGui::GetWindowPos();
			show_pussy = 0;
			ImGui::SetWindowPos(ImVec2(1005, -362));
			no_background = true;
			no_move = true;
			Sleep(120);
		}
		else {
			ImGui::SetWindowPos(lastpos);
			show_pussy = 1;
			no_background = false;
			no_move = false;
			Sleep(120);
		}
	}
	
			ImGui::Text("Executor");
			ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		
					static char text[1024 * 16];
					

					ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16));
					if (ImGui::Button("Execute")) {
						LogToConsole(text);
					}
					static char str0[128];
					ImGui::InputText("", str0, IM_ARRAYSIZE(str0));
					static int i0 = 2;
					ImGui::InputInt("packet type", &i0);
					if (ImGui::Button("send packet")) {
						string p = (string)str0;
						SendPacket(i0, str0, getpeer());

					}
				

		
	


	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return oEndScene(device);
}

HANDLE pHandle;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall PHook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:

		DisableThreadLibraryCalls(hMod);
		mBase = (uintptr_t)GetModuleHandle(NULL);
		pHandle = GetCurrentProcess();

		DWORD oldprotect;
		VirtualProtectEx(pHandle, (LPVOID)(mBase + 0x1F4983), 2, PAGE_EXECUTE_READWRITE, &oldprotect);
		nop_((PVOID)(mBase + 0x1D30AE), 2);
		VirtualProtectEx(pHandle, (LPVOID)(mBase + 0x43FE9C), 2, PAGE_EXECUTE_READWRITE, &oldprotect);
		nop_((PVOID)(mBase + 0x43FE9C), 2);
		ltchook = (mBase + Addr_LogToConsole);
		sphook = (mBase + Addr_SendPacket);
		sprhook = (mBase + Addr_SendPacketRaw);


		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
	
		//DetourAttach(&(PVOID&)ptuphook, &ProcessTankUpdatePacketHook); //removed for several reasons
		DetourTransactionCommit();

		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PHook::Init, hMod, 0, nullptr);
		initOverlay();
		break;
	case DLL_PROCESS_DETACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PHook::Shutdown, hMod, 0, nullptr);
		break;
	}
	return TRUE;
}
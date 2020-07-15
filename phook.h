#pragma once
#include "includes.h"

extern bool init_hook;
extern HWND window;
extern void* pDevice[119];
extern PTR EndSceneAddress;
extern EndScene oEndScene;
extern WNDPROC oWndProc;
extern bool initialized;

namespace PHook
{
	void Init();
	void Shutdown();
	long __stdcall hkEndScene(LPDIRECT3DDEVICE9 device);
	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}
// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <iostream>;
using namespace std;
#include <windows.h>;
#include <tlhelp32.h>;
#include <tchar.h>;

DWORD ProcessFind(LPCTSTR Exename);//进程名称查找进程ID

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//MessageBox(NULL, L"Process attach!", L"Inject All The Things!", 0);
		char szExePath[MAX_PATH];
		char szInfo[MAX_PATH + 100];

		GetModuleFileNameA(NULL, szExePath, MAX_PATH);
		wsprintfA(szInfo, "I'm in Process(%d),Path:%s", ProcessFind(TEXT("notepad.exe")), szExePath);
		MessageBoxA(NULL, szInfo, "2021-01-10", 0);
		break;
	case DLL_THREAD_ATTACH:
		//MessageBox(NULL, L"Thread attach!", L"Inject All The Things!", 0);
		break;
	case DLL_THREAD_DETACH:
		//MessageBox(NULL, L"Thread detach!", L"Inject All The Things!", 0);
		break;
	case DLL_PROCESS_DETACH:
		//MessageBox(NULL, L"Process detach!", L"Inject All The Things!", 0);
		break;
	}
	return TRUE;
}

//进程名称查找进程ID
DWORD ProcessFind(LPCTSTR Exename) //进程名称
{
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (!hProcess)
	{
		return FALSE;
	}
	PROCESSENTRY32 info;
	info.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcess, &info))
	{
		return FALSE;
	}
	while (TRUE)
	{

		cout << endl;
		if (_tcscmp(info.szExeFile, Exename) == 0)
		{
			return info.th32ProcessID;//返回进程的ID
		}
		if (!Process32Next(hProcess, &info))
		{
			return FALSE;
		}
	}
	return FALSE;

}


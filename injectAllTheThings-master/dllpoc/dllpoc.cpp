#include <windows.h>
#include <stdio.h>
#include <iostream>;
using namespace std;
#include <tlhelp32.h>;
#include <tchar.h>;

DWORD ProcessFind(LPCTSTR Exename);//进程名称查找进程ID
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
HWND GetMainWindow();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	HWND hWnd;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hWnd = GetMainWindow();
         if (hWnd)
             hWnd = ::FindWindowEx(hWnd, 0, TEXT("EDIT"), NULL);
         if (hWnd)
         {
             ::MessageBox(hWnd, TEXT("开始注入"), TEXT("提示"), MB_OK);
             for (int i = 0; i < 100; i++)
             {
                 PostMessageW(hWnd, WM_CHAR, L'逆', 1);
                 PostMessageW(hWnd, WM_CHAR, L'向', 1);
                 PostMessageW(hWnd, WM_CHAR, L'工', 1);
                 PostMessageW(hWnd, WM_CHAR, L'程', 1);
                 PostMessageW(hWnd, WM_KEYDOWN, VK_RETURN, 1);
             }
         }
         else
         {
             ::MessageBox(hWnd, TEXT("记事本不存在"), TEXT("提示"), MB_OK);
         }
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

//extern "C" __declspec(dllexport) int poc(int code, WPARAM wParam, LPARAM lParam) {
extern "C" __declspec(dllexport) BOOL cuc() {
	char szExePath[MAX_PATH];
	char szInfo[MAX_PATH + 100];

	//GetModuleFileNameA(NULL, szExePath, MAX_PATH);
	wsprintfA(szInfo, "Notepad is in(%d)", ProcessFind(TEXT("notepad.exe")));//找到记事本
	MessageBoxA(NULL, szInfo, "2021-01-10", 0);

	//return(CallNextHookEx(NULL, code, wParam, lParam));
	return TRUE;
}

extern "C" __declspec(dllexport) BOOL beijing() {
	MessageBox(NULL, L"POC called", L"Inject All The Things!", 0);
	//return(CallNextHookEx(NULL, code, wParam, lParam));
	return TRUE;
}

//BOOL beijing() {
//	MessageBox(NULL, L"POC called", L"Inject All The Things!", 0);
//	//return(CallNextHookEx(NULL, code, wParam, lParam));
//}

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
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
 {
     DWORD dwCurProcessId = *((DWORD*)lParam);
     DWORD dwProcessId = 0;

     GetWindowThreadProcessId(hwnd, &dwProcessId);
     if (dwProcessId == dwCurProcessId && GetParent(hwnd) == NULL)
     {
		* ((HWND *)lParam) = hwnd;
         return FALSE;
     }
     return TRUE;
 }
HWND GetMainWindow()
 {
     DWORD dwCurrentProcessId = ProcessFind(TEXT("notepad.exe"));
     if (!EnumWindows(EnumWindowsProc, (LPARAM)&dwCurrentProcessId))
     {
         return (HWND)dwCurrentProcessId;
     }
     return NULL;
 }
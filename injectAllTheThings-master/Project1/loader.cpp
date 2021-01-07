#include<Windows.h>
#include<stdio.h>

typedef BOOL(*CUC_PROC_ADDR)();

int main() {
	HMODULE hModule = LoadLibraryA("dllpoc.dll");

	if (hModule == NULL)
	{
		printf("LoadLibraryA Error(%d)", GetLastError());
		return 0;
	}
	//LoadLibraryA("dllmain_32.dll");
	CUC_PROC_ADDR cuc_ptr = (CUC_PROC_ADDR)GetProcAddress(hModule, "cuc");
	//void* cuc = GetProcAddress(hModule, "cuc");
	
	void* bj = GetProcAddress(hModule, "beijing");
	printf("cuc function addr: %p,beijing function addr: %p", cuc_ptr,bj);
	cuc_ptr();
}
//
//修改成x64 并重新生成解决方案 修改路径
//inject....exe -t 1 notepad.exe (路径)\dllmain.dll 


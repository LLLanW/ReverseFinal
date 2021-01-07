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
//�޸ĳ�x64 ���������ɽ������ �޸�·��
//inject....exe -t 1 notepad.exe (·��)\dllmain.dll 


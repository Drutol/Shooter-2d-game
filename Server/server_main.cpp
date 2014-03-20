#pragma comment(lib, "Ws2_32.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

SOCKADDR_IN addr;

SOCKET sListen;
SOCKET sConnect;
SOCKET* Connections;

using namespace std;

struct DataPkg
{
	int x;
	int y;
};
struct HelloMsg
{
	int ID;
	int wait;
};


int addrlen = sizeof(addr);
int ConCounter = 0;


int ServerThread(int ID1)
{
	DataPkg data1,data2;
	int ID2 = ID1 - 1;
	char* client_1_string_recv = new char [sizeof(DataPkg)];
	char* client_2_string_recv = new char [sizeof(DataPkg)];
	char* client_1_string_to_send = new char [sizeof(DataPkg)];
	char* client_2_string_to_send = new char [sizeof(DataPkg)];
	bool data_received_1 = false;
	bool data_received_2 = false;
	for(;;Sleep(0.016))
	{

		
		//ZeroMemory(client_1_string,sizeof(client_1_string));
		if(recv(Connections[ID1],client_1_string_recv,sizeof(data1),NULL))
		{
			memcpy(&data1,client_1_string_recv,sizeof(DataPkg));
			data_received_1=true;
		}

		//ZeroMemory(client_2_string,sizeof(client_2_string));
		if(recv(Connections[ID2],client_2_string_recv,sizeof(data2),NULL))
		{
			memcpy(&data2,client_2_string_recv,sizeof(DataPkg));
			data_received_2=true;
		}
		if(data_received_1&&data_received_2)
		{
			memcpy(client_1_string_to_send,&data1,sizeof(DataPkg));
			memcpy(client_2_string_to_send,&data2,sizeof(DataPkg));
			
			send(Connections[ID1],client_2_string_to_send,sizeof(DataPkg),NULL);
			send(Connections[ID2],client_1_string_to_send,sizeof(DataPkg),NULL);
			data_received_1=data_received_2=false;
		}

	}
	return 0;
}

int InitWinSock()
{
	int RetVal = 0;
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2,1);
	RetVal = WSAStartup(DllVersion, &wsaData);

	return RetVal;
}

int main()
{
	int RetVal = 0;
	RetVal = InitWinSock();
	cout<<"Initializing..."<<endl;
	if(RetVal != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	cout<<"...Done"<<endl<<"Creating sockets..."<<endl;
	Connections = (SOCKET*)calloc(64, sizeof(SOCKET));

	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	sConnect = socket(AF_INET, SOCK_STREAM, NULL);

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port        = htons(2525);
	addr.sin_family      = AF_INET;

	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	
	listen(sListen, 64);
	cout<<"...Done"<<endl<<"Starting main server function on 127.0.0.1:2525..."<<endl;
	char* hello_string = new char[sizeof(HelloMsg)];
	for(;; Sleep(0.016))
	{
		if(sConnect = accept(sListen, (SOCKADDR*)&addr, &addrlen))
		{
			HelloMsg hello_msg;
			ZeroMemory(&hello_msg,sizeof(hello_msg));
			ZeroMemory(hello_string,sizeof(hello_string));
			cout<<"New connection accepted : "<<ConCounter+1<<endl;
			Connections[ConCounter] = sConnect;
			//char* ID = new char[64];
			hello_msg.ID = ConCounter;

			
			if((ConCounter+1)%2==0&&ConCounter!=0)
			{
					hello_msg.wait = 0;
					memcpy(hello_string,&hello_msg,sizeof(HelloMsg));
					send(Connections[ConCounter],hello_string,sizeof(HelloMsg),NULL);
					send(Connections[ConCounter-1],hello_string,sizeof(HelloMsg),NULL);
					cout<<"Single Client info sent -> "<<hello_msg.ID<<" : "<<hello_msg.wait<<endl;
					cout<<"Pair info Sent"<<endl;
			}
			if((ConCounter+1)%2==1)
			{
				hello_msg.wait = 1; 
				memcpy(hello_string,&hello_msg,sizeof(HelloMsg));
				send(Connections[ConCounter],hello_string,sizeof(HelloMsg),NULL);
				cout<<"Single Client info sent -> "<<hello_msg.ID<<" : "<<hello_msg.wait<<endl;
			}
			
			if((ConCounter+1)%2==0&&ConCounter!=0)
				{
					CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) ServerThread, (LPVOID)(ConCounter), NULL, NULL);
					cout<<"Users paired - creating new thread"<<endl;	
				}
			
			ConCounter++;
		}
	}

	return 0;
}


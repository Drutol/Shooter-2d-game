#include "Multiplayer_Client.h"
#include "GameFunctions.h"
coords online_player;
SOCKET MultiPlayer::sConnect;
MultiPlayer::Multiplayer_Client::Multiplayer_Client(void)
{
}


MultiPlayer::Multiplayer_Client::~Multiplayer_Client(void)
{
}

bool MultiPlayer::Multiplayer_Client::attempt_connection(std::string host)
{
	if(set_up_sockets(host))
	{
		if(connect_to_server())
		{
			if(wait_for_hello_message())
			{
				cout<<"Connection established"<<endl;
				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) receive_send_data, this, NULL, NULL);
				return true;
			}
		}
	}
}


bool MultiPlayer::Multiplayer_Client::set_up_sockets(std::string host)
{
	int RetVal = 0;

	WSAData wsaData;
	WORD Version = MAKEWORD(2,1);
	RetVal = WSAStartup(Version, &wsaData);
	if(RetVal != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	else
	{
		sConnect = socket(AF_INET, SOCK_STREAM, NULL);

		addr.sin_addr.s_addr = inet_addr(host.c_str());
		addr.sin_port        = htons(2525);
		addr.sin_family      = AF_INET;
		return true;
	}
}

bool MultiPlayer::Multiplayer_Client::connect_to_server()
{
	int RetVal = connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));

	if(RetVal != 0)
	{
		MessageBoxA(NULL, "Could not connect to server", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	else
		return true;
}

int MultiPlayer::Multiplayer_Client::wait_for_hello_message()
{
	HelloMsg hello_msg;
	char* msg = new char [sizeof(hello_msg)];
	if(recv(sConnect, msg, sizeof(hello_msg), NULL))
	{
		memcpy(&hello_msg,msg,sizeof(HelloMsg));
		cout<<hello_msg.ID<<" : "<<hello_msg.wait<<endl;
		if(hello_msg.wait==1)
		{
				//MessageBoxA(NULL, "Searching for 2nd player - esc to leave", "Wait", MB_OK | MB_ICONEXCLAMATION);
				cout<<"Searching for 2nd player"<<endl;
				for(;;Sleep(1))
				{
					cout<<"Waiting for update"<<endl;
					if(recv(sConnect, msg, sizeof(hello_msg), NULL))
					{
						cout<<"received sth"<<endl;
						memcpy(&hello_msg, msg, sizeof(HelloMsg));
						if(hello_msg.wait==0)
							return true;
					}

				}
		}
		else if(hello_msg.wait==0)
				return true;
		
	}
	return false;

}

void MultiPlayer::receive_send_data()
{
	char * string_to_send = new char [sizeof(DataPkg)];
	char * msg = new char [sizeof(DataPkg)];
	ZeroMemory(string_to_send,sizeof(string_to_send));
	ZeroMemory(msg,sizeof(msg));
	DataPkg data;
	DataPkg data_recv;
	for(;;Sleep(0.016))
	{
		data.x=player.PosX;
		data.y=player.PosY;
		memcpy(string_to_send,&data,sizeof(DataPkg));
		send(sConnect,string_to_send,sizeof(DataPkg),NULL);

		if(recv(sConnect,msg,sizeof(data_recv),NULL))
		{
			memcpy(&data_recv,msg,sizeof(DataPkg));
			online_player=data_recv;
		}
	}

}

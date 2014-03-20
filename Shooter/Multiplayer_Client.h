#pragma once
#include "link.h"
#include "GameFunctions.h"
namespace MultiPlayer
{
struct HelloMsg
{
	int ID;
	int wait;
};
extern SOCKET sConnect;
class Multiplayer_Client
{
private:
	SOCKADDR_IN addr;
	bool set_up_sockets(std::string host);
	bool connect_to_server();
	int wait_for_hello_message();
public:
	Multiplayer_Client(void);
	~Multiplayer_Client(void);
	bool attempt_connection(std::string host="127.0.0.1");
};

void receive_send_data();
}
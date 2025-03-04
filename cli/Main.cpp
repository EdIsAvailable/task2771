#include<iostream>
#include <vector>
#include <string>
#include "Acc.h"
#include "Chat.h"
#include "Server.h"
using namespace std;

Server* _server;

int main()
{
	//setlocale(LC_ALL, "ru_RU.UTF-8");

	_server = new Server();
	_server->MainProcess();

	return 0;
};




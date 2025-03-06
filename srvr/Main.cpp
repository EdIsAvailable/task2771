#include <cstdio>
#include <iostream>
#include "Acc.h"
#include "Socket.h"
#include "Chat.h"
#include "Server.h"
#include "db.h"
#include "NewUser.h"
#include "Logger.h"

using namespace std;

Server* _server;
Logger* _logger;
int main()
{

    _server = new Server();
    _server->MainProcess();
    _logger = new Logger();
    delete _server; //  освободить память
    delete _logger;
    return 0;
}


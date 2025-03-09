#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>
#include "Acc.h"
#include "Socket.h"
#include "Chat.h"
#include "Server.h"
#include "db.h"
#include "NewUser.h"
#include "Logger.h"

using namespace std;

Server* _server;

int main() {

    //Logger logger;
    _server = new Server();
    _server->MainProcess();
    //_logger = new Logger();
    //  освободим память
    delete _server; 
    //delete _logger;
    return 0;
}


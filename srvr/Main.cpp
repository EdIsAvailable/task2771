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

    _server = new Server();
    _server->MainProcess();

    delete _server; 
    return 0;
}


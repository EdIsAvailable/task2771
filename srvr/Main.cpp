#include <cstdio>
#include<iostream>
#include "Acc.h"
#include "Socket.h"
#include "Chat.h"
#include "Server.h"
#include "db.h"
#include "NewUser.h"


using namespace std;

Server* _server;
//Driver* driver;
int main()
{
    //registerUser("Alice", "default_hash");
    //registerUser("Bob", "default_hash");

    //saveMessage("Alice", "Bob", "Hello, Bob!");
    //fetchMessages("Bob");

    _server = new Server();
    _server->MainProcess();

    delete _server; //  освободить память
    return 0;
}


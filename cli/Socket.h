#pragma once
#include<string>
#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<memory.h>

class Socket
{
public:
    Socket();
    ~Socket();
    //int connectServerOpen();
    int connectClientOpen();
    void sendMessage(int connection, std::string &str);// отправить
    std:: string reseiveMessage(int connection);
    void connectClose(int socket_discriptor);
};

/*#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Acc.h"
#include "Message.h"
#include "db.h" // Include DB header for database operations
#include <mysql_driver.h>
#include <mysql_connection.h>
using namespace std;

class Chat
{
private:
    vector<Message*> _messages; // Vector to store all user messages
public:
    Chat();
     std::unique_ptr<sql::Connection> connectToDatabase(); // Declare the function here
   //sql::Connection* connectToDatabase(); // Объявление функции

    // Method to add a message to the chat
    void AddMessage(const string& userFrom, const string& userTo, const string& text);

    // Method to display all messages
    void ViewAllMessages(void);

    // Method to display messages for a specific user
    void ViewMessagesForUser(Acc* user);

    // Method to display messages addressed to all users
    void ViewMessagesForAllUsers(Acc* user);

    // Method to fetch and display all messages from the database
    void fetchAllMessages(); // Declaration of the fetchAllMessages method

    // Destructor to clean up resources
    ~Chat();
};
*/

#ifndef CHAT_H
#define CHAT_H

#include <string>
#include <memory>
#include "db.h" // Подключаем файл с функциями работы с БД

class Chat {
public:
    Chat();
    void AddMessage(const std::string& userFrom, const std::string& userTo, const std::string& text);
    void ViewAllMessages(void);
    void ViewMessagesForUser(const std::string& login);
    void ViewMessagesForAllUsers(void);
    ~Chat();
};

#endif // CHAT_H
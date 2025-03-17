
/*#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <functional>
#include "db.h"     // Подключаем файл с функциями работы с БД
#include "Logger.h" // Подключаем файл с функциями записи в log.txt

class Chat {
public:
    Chat();
    
    void AddMessage(const std::string& userFrom, const std::string& userTo, const std::string& text);
    void ViewAllMessages();
    void ViewMessagesForUser(const std::string& login);
    void ViewMessagesForAllUsers();
    void ViewAllMessagesFromLog();
    void ViewMessagesForUserLog(const std::string& login);
    void ViewMessagesForAllUsersLog();
    ~Chat();

private:
    Logger logger;

    void filterAndDisplayLog(const std::function<bool(const std::string&)>& filter, const std::string& header);
};

*/

#ifndef CHAT_H
#define CHAT_H

#include <string>
#include <memory>
#include "Logger.h"

class Chat {
public:
    Chat();
    void AddMessage(const std::string& userFrom, const std::string& userTo, const std::string& text);
    void ViewAllMessages(void);
    void ViewMessagesForUser(const std::string& login);
    void ViewMessagesForAllUsers(void);
    ~Chat();

private:
    Logger logger;
};

#endif // CHAT_H
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
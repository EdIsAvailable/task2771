#ifndef CHAT_H
#define CHAT_H

#include <string>
#include <memory>
#include "db.h" // Подключаем файл с функциями работы с БД
#include "Logger.h" // Подключаем файл с функциями записи в log.txt

class Chat {
public:
    Chat();
    void AddMessage(const std::string& userFrom, const std::string& userTo, const std::string& text);
    void ViewAllMessages(void);
    void ViewMessagesForUser(const std::string& login);
    void ViewMessagesForAllUsers(void);
    void ViewAllMessagesFromLog(void);
    void ViewMessagesForUserLog(const std::string& login);
    void ViewMessagesForAllUsersLog(void);
    ~Chat();

    private:
    Logger logger; // Объект Logger для работы с логами

};

#endif // CHAT_H
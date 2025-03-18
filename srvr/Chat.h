#pragma once

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

#include "Chat.h"
#include <iostream>

// Конструктор
Chat::Chat() {}

// Добавление сообщения в лог
void Chat::AddMessage(const std::string& userFrom, const std::string& userTo, const std::string& text) {
    std::string message = "От: " + userFrom + " | Кому: " + userTo + " | Сообщение: " + text;
    saveMessage(userFrom, userTo, text);
    logger.writeLog(message);
}

void Chat::ViewAllMessages() {
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT SenderID, ReceiverID, MessageText, Timestamp FROM Messages"
        ));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "Всего сообщений в базе:" << std::endl;
        while (res->next()) {
            int senderID = res->getInt("SenderID");
            int receiverID = res->getInt("ReceiverID");
            std::string messageText = res->getString("MessageText");
            std::string timestamp = res->getString("Timestamp");

            std::cout << "От: " << senderID << " | Кому: " << receiverID
                      << " | Сообщение: " << messageText
                      << " | Время: " << timestamp << std::endl;
        }
    } catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Chat::ViewMessagesForUser (const std::string& login) {
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT SenderID, MessageText, Timestamp FROM Messages "
            "WHERE ReceiverID = (SELECT UserID FROM Users WHERE Username = ?)"
        ));
        pstmt->setString(1, login);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "Сообщения для пользователя " << login << ":" << std::endl;
        while (res->next()) {
            int senderID = res->getInt("SenderID");
            std::string messageText = res->getString("MessageText");
            std::string timestamp = res->getString("Timestamp");

            std::cout << "От: " << senderID << " | Сообщение: " << messageText
                      << " | Время: " << timestamp << std::endl;
        }
    } catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Chat::ViewMessagesForAllUsers() {
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT SenderID, MessageText, Timestamp FROM Messages "
            "WHERE ReceiverID = (SELECT UserID FROM Users WHERE Username = 'ALL')"
        ));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "Сообщения для всех пользователей:" << std::endl;
        while (res->next()) {
            int senderID = res->getInt("SenderID");
            std::string messageText = res->getString("MessageText");
            std::string timestamp = res->getString("Timestamp");

            std::cout << "От: " << senderID << " | Сообщение: " << messageText
                      << " | Время: " << timestamp << std::endl;
        }
    } catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Просмотр всех сообщений из лога
void Chat::ViewAllMessagesFromLog() {
    logger.resetReadPosition(); // Сбрасываем указатель чтения
    std::string line;
    std::cout << "Все сообщения из лога:" << std::endl;
    while (!(line = logger.readLog()).empty()) {
        std::cout << line << std::endl;
    }
}

// Фильтрация и отображение логов
void Chat::filterAndDisplayLog(const std::function<bool(const std::string&)>& filter, const std::string& header) {
    logger.resetReadPosition(); // Сбрасываем указатель чтения
    std::string line;
    std::cout << header << std::endl;
    while (!(line = logger.readLog()).empty()) {
        if (filter(line)) {
            std::cout << line << std::endl;
        }
    }
}

void Chat::ViewMessagesForUserLog(const std::string& login) {
    filterAndDisplayLog(
        [&login](const std::string& line) { return line.find("Кому: " + login) != std::string::npos; },
        "Сообщения для пользователя из лога " + login + ":"
    );
}

void Chat::ViewMessagesForAllUsersLog() {
    filterAndDisplayLog(
        [](const std::string& line) { return line.find("Кому: ALL") != std::string::npos; },
        "Сообщения для всех пользователей из лога:"
    );
}

Chat::~Chat() {
   
}
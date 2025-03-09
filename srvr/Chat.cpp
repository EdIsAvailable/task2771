#include "Chat.h"
#include <iostream>

using namespace std;

// Конструктор
Chat::Chat() : logger("log.txt") {}
// Добавление сообщения в лог
void Chat::AddMessage(const std::string& userFrom, const std::string& userTo, const std::string& text) {
    string message = "От: " + userFrom + " | Кому: " + userTo + " | Сообщение: " + text;
    logger.writeLog(message);
}
void Chat::ViewAllMessages(void) {
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT SenderID, ReceiverID, MessageText, Timestamp FROM Messages"
        ));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        cout << "Всего сообщений в базе:" << endl;
        while (res->next()) {
            int senderID = res->getInt("SenderID");
            int receiverID = res->getInt("ReceiverID");
            string messageText = res->getString("MessageText");
            string timestamp = res->getString("Timestamp");

            cout << "От: " << senderID << " | Кому: " << receiverID
                << " | Сообщение: " << messageText
                << " | Время: " << timestamp << endl;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
    }
}

void Chat::ViewMessagesForUser(const std::string& login) {
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT SenderID, MessageText, Timestamp FROM Messages "
            "WHERE ReceiverID = (SELECT UserID FROM Users WHERE Username = ?)"
        ));
        pstmt->setString(1, login);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        cout << "Сообщения для пользователя " << login << ":" << endl;
        while (res->next()) {
            int senderID = res->getInt("SenderID");
            string messageText = res->getString("MessageText");
            string timestamp = res->getString("Timestamp");

            cout << "От: " << senderID << " | Сообщение: " << messageText
                << " | Время: " << timestamp << endl;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
    }
}

void Chat::ViewMessagesForAllUsers(void) {
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT SenderID, MessageText, Timestamp FROM Messages "
            "WHERE ReceiverID = (SELECT UserID FROM Users WHERE Username = 'ALL')"
        ));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        cout << "Сообщения для всех пользователей:" << endl;
        while (res->next()) {
            int senderID = res->getInt("SenderID");
            string messageText = res->getString("MessageText");
            string timestamp = res->getString("Timestamp");

            cout << "От: " << senderID << " | Сообщение: " << messageText
                << " | Время: " << timestamp << endl;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
    }
}

// Просмотр всех сообщений из лога
void Chat::ViewAllMessagesFromLog(void) {
    logger.readLog(); // Сбрасываем указатель чтения
    string line;
    cout << "Все сообщения из лога:" << endl;
    while (!(line = logger.readLog()).empty()) {
        cout << line << endl;
    }
}

// Просмотр сообщений для конкретного пользователя из лога
void Chat::ViewMessagesForUserLog(const std::string& login) {
    logger.readLog(); // Сбрасываем указатель чтения
    string line;
    cout << "Сообщения для пользователя из лога" << login << ":" << endl;
    while (!(line = logger.readLog()).empty()) {
        if (line.find("Кому: " + login) != string::npos) {
            cout << line << endl;
        }
    }
}

// Просмотр сообщений для всех пользователей из лога
void Chat::ViewMessagesForAllUsersLog(void) {
    logger.readLog(); // Сбрасываем указатель чтения
    string line;
    cout << "Сообщения для всех пользователей из лога:" << endl;
    while (!(line = logger.readLog()).empty()) {
        if (line.find("Кому: ALL") != string::npos) {
            cout << line << endl;
        }
    }
}

Chat::~Chat() {
    // В данном случае не нужно освобождать память для сообщений, так как они хранятся в БД и log.txt
}
#include "Chat.h"
#include "db.h"
#include <iostream>

using namespace std;

Chat::Chat() : logger("log.txt") {} // Инициализируем файл logger по умолчанию

void Chat::AddMessage(const std::string& userFrom, const std::string& userTo, const std::string& text) {
    try {
        // Сохраняем сообщение в базе данных
        saveMessage(userFrom, userTo, text);
        
        // Записываем сообщение в лог с подробной информацией
        std::string logMessage = "От '" + userFrom + "' Для '" + userTo + "': " + text;
        logger.writeLog(logMessage);
        
        std::cout << "Сообщение успешно сохранено!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << " Ошибка сохранения сообщения: " << e.what() << std::endl;
        logger.writeLog("ERROR: Failed to save message - " + std::string(e.what()));
    }
}
void Chat::ViewAllMessages(void) {
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT SenderID, ReceiverID, MessageText, Timestamp FROM Messages"
        ));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        cout << "Все сообщения в БД:" << endl;
        while (res->next()) {
            int senderID = res->getInt("SenderID");
            int receiverID = res->getInt("ReceiverID");
            string messageText = res->getString("MessageText");
            string timestamp = res->getString("Timestamp");

            cout << "От: " << senderID << " | To: " << receiverID
                << " | Сообщение: " << messageText
                << " | Время: " << timestamp << endl;
        }
        
        // Лог просмотров
        logger.writeLog("Сообщения просмотрены");
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
        logger.writeLog("SQL error in ViewAllMessages: " + string(e.what()));
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
        
        // Лог просмотров
        logger.writeLog("Сообщения для пользователя: " + login);
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
        logger.writeLog("SQL error in ViewMessagesForUser: " + string(e.what()));
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

        cout << "Messages for all users:" << endl;
        while (res->next()) {
            int senderID = res->getInt("SenderID");
            string messageText = res->getString("MessageText");
            string timestamp = res->getString("Timestamp");

            cout << "From: " << senderID << " | Message: " << messageText
                << " | Time: " << timestamp << endl;
        }
        
        // Лог просмотров
        logger.writeLog("Сообщения для всех пользователей");
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
        logger.writeLog("SQL error in ViewMessagesForAllUsers: " + string(e.what()));
    }
}

Chat::~Chat() {
    // Не требуется очищение памяти
    logger.writeLog("Экземпляр чата удалён");
}
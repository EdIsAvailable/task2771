#include "db.h"

// Функция для подключения к базе данных
std::unique_ptr<sql::Connection> connectToDatabase() {
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
    std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", "123"));
    con->setSchema("chatdb");
    return con;
}

// Функция для регистрации нового пользователя
void registerUser(const std::string& username, const std::string& passwordHash) {
    try {
        auto con = connectToDatabase();

        // Проверка на существование пользователя
        std::unique_ptr<sql::PreparedStatement> checkStmt(con->prepareStatement(
            "SELECT UserID FROM Users WHERE Username = ?"
        ));
        checkStmt->setString(1, username);
        std::unique_ptr<sql::ResultSet> checkRes(checkStmt->executeQuery());

        if (checkRes->next()) {
            std::cout << "User  already exists with UserID: " << checkRes->getInt(1) << std::endl; // Используем индекс
            return;
        }

        // Вставка нового пользователя
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "INSERT INTO Users (Username, PasswordHash) VALUES (?, ?)"
        ));
        pstmt->setString(1, username);
        pstmt->setString(2, passwordHash); // Добавляем хэш пароля
        pstmt->executeUpdate();

        std::cout << "User  registered successfully!" << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
    }
}

void saveMessage(const std::string& sender, const std::string& receiver, const std::string& message) {
    try {
        auto con = connectToDatabase();

        // Получаем SenderID
        std::unique_ptr<sql::PreparedStatement> senderStmt(con->prepareStatement(
            "SELECT UserID FROM Users WHERE Username = ?"
        ));
        senderStmt->setString(1, sender);
        std::unique_ptr<sql::ResultSet> senderRes(senderStmt->executeQuery());

        if (!senderRes->next()) {
            std::cerr << "Sender not found!" << std::endl;
            return;
        }
        int senderID = senderRes->getInt(1); // Используем индекс

        // Получаем ReceiverID
        std::unique_ptr<sql::PreparedStatement> receiverStmt(con->prepareStatement(
            "SELECT UserID FROM Users WHERE Username = ?"
        ));
        receiverStmt->setString(1, receiver);
        std::unique_ptr<sql::ResultSet> receiverRes(receiverStmt->executeQuery());

        if (!receiverRes->next()) {
            std::cerr << "Receiver not found!" << std::endl;
            return;
        }
        int receiverID = receiverRes->getInt(1); // Используем индекс

        // Вставка сообщения
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "INSERT INTO Messages (SenderID, ReceiverID, MessageText) VALUES (?, ?, ?)"
        ));
        pstmt->setInt(1, senderID); // Устанавливаем SenderID
        pstmt->setInt(2, receiverID); // Устанавливаем ReceiverID
        pstmt->setString(3, message); // Устанавливаем текст сообщения

        pstmt->executeUpdate();
        std::cout << "Message saved successfully!" << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
    }
}
void fetchMessages(const std::string& receiver) {
    try {
        auto con = connectToDatabase();

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT SenderID, MessageText, Timestamp FROM Messages "
            "WHERE ReceiverID = (SELECT UserID FROM Users WHERE Username = ?)"
        ));
        pstmt->setString(1, receiver);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            std::cout << "From: " << res->getInt("SenderID")
                << " | Message: " << res->getString("MessageText")
                << " | At: " << res->getString("Timestamp") << std::endl;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
    }
}

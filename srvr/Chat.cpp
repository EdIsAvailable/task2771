#include "Chat.h"
#include "db.h"
#include <iostream>

using namespace std;

Chat::Chat() : logger("log.txt") {} // Initialize logger with default filename

void Chat::AddMessage(const std::string& userFrom, const std::string& userTo, const std::string& text) {
    try {
        // Save message to database
        saveMessage(userFrom, userTo, text);
        
        // Log the message action with more detailed information
        std::string logMessage = "Message from '" + userFrom + "' to '" + userTo + "': " + text;
        logger.writeLog(logMessage);
        
        std::cout << "Message saved successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving message: " << e.what() << std::endl;
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

        cout << "All messages in database:" << endl;
        while (res->next()) {
            int senderID = res->getInt("SenderID");
            int receiverID = res->getInt("ReceiverID");
            string messageText = res->getString("MessageText");
            string timestamp = res->getString("Timestamp");

            cout << "From: " << senderID << " | To: " << receiverID
                << " | Message: " << messageText
                << " | Time: " << timestamp << endl;
        }
        
        // Log the view action
        logger.writeLog("Viewed all messages");
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

        cout << "Messages for user " << login << ":" << endl;
        while (res->next()) {
            int senderID = res->getInt("SenderID");
            string messageText = res->getString("MessageText");
            string timestamp = res->getString("Timestamp");

            cout << "From: " << senderID << " | Message: " << messageText
                << " | Time: " << timestamp << endl;
        }
        
        // Log the view action
        logger.writeLog("Viewed messages for user: " + login);
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
        
        // Log the view action
        logger.writeLog("Viewed messages for all users");
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
        logger.writeLog("SQL error in ViewMessagesForAllUsers: " + string(e.what()));
    }
}

Chat::~Chat() {
    // No need to free memory for messages as they're stored in the database
    logger.writeLog("Chat instance destroyed");
}
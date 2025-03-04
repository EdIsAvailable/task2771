/*#include "Chat.h"
#include <iostream>
using namespace std;

Chat::Chat() {}
//Chat::Chat(vector<Message*> _messages) : _messages(messages) {}
//Chat::Chat(vector<Message*> GetMessagesForAll) : _GetMessagesForAll{}
//Chat::vector<Message*> GetMessagesForUser(string login){}

void Chat::AddMessage(const std::string& userFrom, const std::string& userTo, const std::string& text)
{
    _messages.push_back(new Message(userFrom, userTo, text));
}

void Chat::ViewAllMessages(void)
{
	int msgId = (int)_messages.size();
	cout << "Всего сообщений в базе: " << msgId << endl;

	// Количество сообщений равно количеству зарегистрированных пользователей в данном тесте
	while (msgId--) {  // Обратный отсчёт
		_messages[msgId]->Show();  // Выводим содержимое вектора сообщений
	}
}
// Вывод сообщений для пользователя login из вектора сообщений
void Chat::ViewMessagesForUser(Acc* user)
{
	std::cout << "У вас есть новые сообщения для пользователя: ";
	string login = user->getLogin(); // Получаем логин получателя сообщений
	std::cout << login << " в прошлый раз Вы остановились на сообщении #: ";
	int lastReadMsg = user->getLastReadMsg(); // Последнее прочитанное сообщение пользователем
	//int firstMsg = 0;
	std::cout << lastReadMsg << " всего сейчас в базе: ";
	int msgId = (int)_messages.size(); // Получаем количество всех сообщений в векторе
	std::cout << msgId << " сообщений.\n";
	// Выводим сообщения пользователя от последнего прочитанного до последнего в векторе
	while (lastReadMsg <  msgId) {
		if(_messages[lastReadMsg]->getUserTo() == login)
		{
			_messages[lastReadMsg]->Show(); // Выводим содержимое вектора сообщений
			user->setLastReadMsg(lastReadMsg); // 
		}
		lastReadMsg++;
	}
}
// Вывод сообщений адресованых всем пользователям из вектора сообщений
void Chat::ViewMessagesForAllUsers(Acc* user)
{
	// Вывод сообщений для пользователя login из вектора сообщений
	int msgId = (int)_messages.size();
	// Количество сообщений равно количеству зарегистрированных пользователей в данном тесте
	while (msgId--) {  // Обратный отсчёт
		if (_messages[msgId]->getUserTo() == "ALL")
			_messages[msgId]->Show(); // Выводим содержимое вектора сообщений
	}
}
Chat::~Chat()
{
	_messages.clear();
};

*/

#include "Chat.h"
#include <iostream>

using namespace std;

Chat::Chat() {}

void Chat::AddMessage(const std::string& userFrom, const std::string& userTo, const std::string& text) {
    // Сохраняем сообщение в базе данных
    saveMessage(userFrom, userTo, text);
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

Chat::~Chat() {
    // В данном случае не нужно освобождать память для сообщений, так как они хранятся в БД
}
#include "Chat.h"
#include <iostream>
using namespace std;

Chat::Chat() {}
//Chat::Chat(vector<Message*> _messages) : _messages(messages) {}
//Chat::Chat(vector<Message*> GetMessagesForAll) : _GetMessagesForAll{}
//Chat::vector<Message*> GetMessagesForUser(string login){}

void Chat::AddMessage(string userFrom, string userTo, string text) 
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


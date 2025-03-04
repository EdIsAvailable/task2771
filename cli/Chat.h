#pragma once
#include<iostream>
#include <vector>
#include <string>
#include "Acc.h"
#include "Message.h"
using namespace std;
class Chat
{
	vector<Message*> _messages; // Вектор для хранения всех сообщений пользователей
public:
	Chat();
	//vector<Message*> GetMessagesForAll();
	//vector<Message*> GetMessagesForUser(string login);
	void AddMessage(string userFrom, string userTo, string text);
	// Вывод всех сообщений из вектора сообщений
	void ViewAllMessages(void);
	// Вывод сообщений для пользователя login из вектора сообщений
	void ViewMessagesForUser(Acc* user);
	// Вывод сообщений адресованых всем пользователям из вектора сообщений
	void ViewMessagesForAllUsers(Acc* user);
	~Chat();
};

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

#pragma once
class Message
{
	string _userFrom, _userTo, _text; //тут добавить геттеры
	time_t _now;
public:
	// Конструктор класса Message создаёт сообщение в котором указываем отправителя, получателя и тело сообщения, дата и время отправленного сообщения добавляется автоматически
	Message(string userFrom, string userTo, string text);
	// Показать сообщение, которое хранится в классе
	void Show(void);
	// Получить имя получателя сообщения
	string getUserTo(void);
	// Получить имя отправителя сообщения
	string getUserFrom(void);
	~Message();
};



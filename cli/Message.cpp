#include "Message.h"
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS для localtime

// Конструктор класса Message создаёт сообщение в котором указываем отправителя, получателя и тело сообщения, дата и время отправленного сообщения добавляется автоматически
Message::Message(string userFrom, string userTo, string text) : _userFrom(userFrom), _userTo(userTo), _text(text)
{
    // Определяем переменные для работы с датой и временем
    //time_t t;
    struct tm *t_m;

	// Подготавливаем дату и время
	_now = time(NULL);
	t_m = localtime(&_now);

	// Формируем дату и время отправки сообщения
	string dateSent =" " + std::to_string(t_m->tm_mday) + "-" + std::to_string(t_m->tm_mon+1) + "-" + std::to_string(t_m->tm_year+1900) + 
					" " + std::to_string(t_m->tm_hour) + ":" + std::to_string(t_m->tm_min) + ":" + std::to_string(t_m->tm_sec);
    std::cout << dateSent << endl;
}

// Показать сообщение, которое хранится в классе
void Message::Show(void)
{
	// Определяем переменные для работы с датой и временем
	struct tm* t_m;
	// Подготавливаем дату и время
	t_m = localtime(&_now);
	string dateSent = " " + std::to_string(t_m->tm_mday) + "-" + std::to_string(t_m->tm_mon + 1) + "-" + std::to_string(t_m->tm_year + 1900) +
		" " + std::to_string(t_m->tm_hour) + ":" + std::to_string(t_m->tm_min) + ":" + std::to_string(t_m->tm_sec);
	cout << "Содержимое: " << _text << " отправитель: " << _userFrom << " получатель: " << _userTo << " отправлено: " << dateSent << endl;
}
// Получить имя получателя сообщения
string Message::getUserTo(void)
{
	return _userTo;
}
// Получить имя отправителя сообщения
string Message::getUserFrom(void)
{
	return _userFrom;
}
Message::~Message()
{
	
}

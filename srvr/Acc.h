#pragma once

#include "NewUser.h"

using namespace std;


class Acc : public NewUser
{
	//string& _login; // В классе NewUser
	string _pswd; // Пароль пользователя
	string _name; // Имя пользователя
	int _lastReadMsg; // Последнее прочитанное сообщение из вектора сообщений
public:
	// Конструктор класса Acc создаёт пользователя с ником, паролем, именем, обнуляет счётчик прочитанных сообщений
	Acc(const std::string& login, const std::string& pswd, const std::string& name); // Изменено на const std::string& // Acc(string& login, string& pswd, string& name);
	void Show() override; // Выводит на экран пароль пользователя
	const  string getPswd() const; // Получить пароль пользователя
	void setPswd(const string pwd); // Установить пароль пользователя
	/*const  string getLogin() const;
	void setLogin(const string login);*/
	const  string getName() const; // Получить имя пользователя
	void setName(const string name);  // Установить имя пользователя
	bool CheckPassword(const std::string& pwd); // Проверить пароль пользователя, верный или нет
	void setLastReadMsg(const int lastReadMsg); // Устанавливаем номер последнего прочитанного сообщения
	const int getLastReadMsg(void); // Получить номер последнего прочитанного сообщения
	~Acc() {}; // Деструктор класса
};


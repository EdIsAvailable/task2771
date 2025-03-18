#include "Acc.h"
#include <iostream>
#include<algorithm>

using namespace std;


Acc::Acc(const std::string& login, const std::string& pswd, const std::string& name) : NewUser(login) //Acc::Acc(string& login, string& pswd, string& name) : NewUser(login)
{
	this->setPswd(pswd);
	_name = name;
	_lastReadMsg = 0;
}
void Acc::Show()
{
	cout << "Пароль " << _pswd << endl; // Выводим на экран пароль пользователя
}
const  string Acc::getPswd() const
{
	return _pswd; // Получить пароль пользователя
}
void Acc::setPswd(const string pwd)
{
	if (!checkSymbols(pwd))
	{
		throw  "Содержится недопустимый символ, попробуйте ещё раз";
	}
	_pswd = pwd;
}
bool Acc::CheckPassword(const std::string& pwd)
{
	return _pswd == pwd; // Проверить пароль пользователя, верный или нет
}

const string Acc::getName() const
{
	return _name; // Получить имя пользователя
}

void Acc::setName(const string name)
{
	//check if null then throw
	if (name.size() == 0)
		throw ("укажите имя");

	_name = name;  // Поменять имя пользователя
}

void Acc::setLastReadMsg(const int lastReadMsg)
{
	_lastReadMsg = lastReadMsg; // Устанавливаем номер последнего прочитанного сообщения
}
const int Acc::getLastReadMsg(void)
{
	return _lastReadMsg; // Получить номер последнего прочитанного сообщения
}


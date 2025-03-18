#pragma once

#include<iostream>
#include <string>


using namespace std;

class NewUser
{
protected: string _login; // Логин пользователя

public:
	NewUser() = default;
	NewUser(const string& login);
	virtual ~NewUser() = default;
	virtual void Show() = 0;
	const  string getLogin() const; // Получить логин пользователя
	void setLogin(const string login); // Установить и вывести логин пользователя
	bool checkSymbols(const string login);     //Проверить на соответствие символы в логине
	
};


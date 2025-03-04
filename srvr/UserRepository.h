#pragma once
#include <vector>
#include <string>
#include "Acc.h"

class UserRepository
{
	vector<Acc*> _users; // Вектор для хранения всех пользователей
public:  UserRepository();
		Acc* NewUser();
		Acc* FindUser(string login); // Поиск логина пользователя, существует ли пользователь в векторе пользователей
		Acc* AuthorizeUser(string login, string pwd); // Попытка авторизации пользователя
		int getSize(); // Получить количество зарегистрированных пользователей
		void UsersList(void); // Вывод списка зарегистрированных пользователей
		~UserRepository();
};

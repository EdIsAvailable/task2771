#include "UserRepository.h"
using namespace std;

UserRepository::UserRepository()
{
	// Инициализируем и резервируем первого пользователя в векторе для Public Chat
	string login = "ALL", pwd = "example", name = "Общий чат";
	Acc* publicChat = new Acc(login, pwd, name);
	
	_users.push_back(publicChat);
}

Acc* UserRepository::NewUser()
{
	string login, pwd, name;

	std::cout << "Введите имя: " << endl;
	std::cin.get(); // Очистить буфер ввода перед чтением строки
	getline(cin, name); // Читаем строку ФИО для регистрации пользователя
	std::cout << "Придумайте логин: " << endl;
	getline(cin, login);
	std::cout << "Создайте пароль: " << endl;
	getline(cin, pwd);
	try
	{
		Acc* newUser = new Acc(login, pwd, name);
		newUser->Show();

		_users.push_back(newUser);

		return newUser;
	}
	catch (const char* c)
	{
		cout << c << endl;
	}
}

Acc* UserRepository::FindUser(string login)
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		//Acc* user = _users[i];
		//if (user->get_Login() == login)
		if (_users[i]->getLogin() == login)
			return _users[i];
	}

	return nullptr;
}

Acc* UserRepository::AuthorizeUser(string login, string pwd)
{
	Acc* user = FindUser(login);

	if (user == nullptr)
	{
		std::cout << "Пользователь с логином " << login << " в сети не найден!!!" << endl;
		return nullptr;
	}

	if (!(user->CheckPassword(pwd)))
	{
		std::cout << "Неправильный пароль" << endl;
		return nullptr;
	}

	return user;
}
int UserRepository::getSize(void)
{
	return _users.size();
}
void UserRepository::UsersList(void)
{
	// Всего пользователей
	int dest_uid = _users.size();
	cout << "Зарегистрированные пользователи, всего: " << dest_uid << " шт." << endl;
	while (dest_uid--) {
		// Выводим список зарегистрированных пользователей, пока вектор не пуст и последний элемент равен нулю
		cout << dest_uid << ".\tLogin: \t"<< _users[dest_uid]->getLogin() << "\tИмя: \t\t" << _users[dest_uid]->getName();  // вывести имя
		cout << endl;
	}
}

UserRepository::~UserRepository()
{
	for (Acc* tmp_acc : _users)
	{
		delete tmp_acc;
	}
	_users.clear();
}


#include "Server.h"

Server::Server()
{
	_userRepo = new UserRepository();
	_msgRepo = new Chat();
};

void Server::MainProcess()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
	//setlocale(LC_ALL, "");
	//system("chcp 1251");

	bool process = true;
	char menuOption;
	do {
		cout << "Создать аккаунт введите: 'c'" << endl;
		cout << "Авторизоваться введите:  'a'" << endl;
		cout << "Выход: 'e'" << endl;
		std::cin >> menuOption;
		switch (menuOption)
		{
		case 'c':
		{
			Acc* newUser =  _userRepo->NewUser();
			break;
		}
		case 'a':
		{
			Acc* user = ProcessAuthorization();
			if (user == nullptr)
				continue; //сюда возможно нужно добавить кщё один break, чтобы не было выхода из цикла

			ProcessChat(user);
			break;
		}
		case 'e': {
			// Вывод всех зарегистрированных пользователей
			_userRepo->UsersList();
			// Вывод всех отправленных сообщений
			_msgRepo->ViewAllMessages();

			process = false;
			break;
		}
		}

		cout << endl;
	} while (process);
};

Acc* Server::ProcessAuthorization()
{
	string login, pwd;
	std::cout << "введите логин " << endl;
	std::cin >> login;
	std::cout << "введите пароль " << endl;
	std::cin >> pwd;

	Acc* user = _userRepo->AuthorizeUser(login, pwd);

	if (user == nullptr)
	{
		return nullptr;
	}

	std::cout << "Пользователь авторизован!" << endl;
	_msgRepo->ViewMessagesForUser(user);
	_msgRepo->ViewMessagesForAllUsers(user);
	return user;
}

void Server::ProcessChat(Acc* user)
{
	string text; // Тело сообщения для отправки
	string userFrom = user->getLogin();
	string userTo;

	_userRepo->UsersList();
	std::cout << "Выберите адресата сообщения: ";
	std::cin >> userTo; // Указываем адресата сообщения
	if (!_userRepo->FindUser(userTo))         //  Проверка что данный адресат существует в сети 
	{
		std::cout << "Адресат с таким именем в сети не зарегестрированн\n" << std::endl;
	}
	else
	{
		cout << "Введите сообщение: ";
		cin.get(); // Очистить буфер ввода перед чтением строки
		getline(cin, text); // Читаем строку тела сообщения для отправки
		// "Отправляем сообщение" - Добавляем очередное сообщение в вектор
		_msgRepo->AddMessage(userFrom, userTo, text);
	}
}

Server::~Server()
{
	delete _userRepo;
	delete _msgRepo;
}

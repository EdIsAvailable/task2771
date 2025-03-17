/* #include "Server.h"
#include "UserRepository.h"
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
	std::string login; // Получите логин от пользователя
	std::string password; // Получите пароль от пользователя

	Acc* user = _userRepo->AuthorizeUser(login, password); // Предполагается, что вы получаете логин и пароль
	if (user) {
		_msgRepo->ViewMessagesForUser(user->getLogin()); // Передаем логин
		_msgRepo->ViewMessagesForAllUsers(); // Вызываем без аргументов
	}
	else {
		std::cout << "Ошибка авторизации." << std::endl;
	}

	return user; // Возвращаем указатель на пользователя
}


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
		std::cout << "Адресат c таким именем в сети не зарегестрированн\n" << std::endl;
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
*/
/*
// Дальше исправлена ошибка авторизации. Старый код закомментирован.
#include "Server.h"
#include "UserRepository.h"

Server::Server()
{
   // _userRepo = new UserRepository();
    //_msgRepo = new Chat();

	UserRepository _userRepo;
	Chat _msgRepo;

}

void Server::MainProcess()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    bool process = true;
    char menuOption;
    do {
        std::cout << "Создать аккаунт введите: 'c'\n";
        std::cout << "Авторизоваться введите:  'a'\n";
        std::cout << "Выход: 'e'\n";
        std::cin >> menuOption;
        switch (menuOption)
        {
        case 'c':
        {
            Acc* newUser  = _userRepo.NewUser();
            break;
        }
        case 'a':
        {
            Acc* user = ProcessAuthorization();
            if (user == nullptr) {
                std::cout << "Ошибка авторизации. Попробуйте снова.\n";
                continue; // Возвращаемся к началу цикла
            }

            ProcessChat(user);
            break;
        }
        case 'e':
        {
            // Вывод всех зарегистрированных пользователей
            _userRepo.UsersList();
            // Вывод всех отправленных сообщений
            _msgRepo.ViewAllMessages();

            process = false;
            break;
        }
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            break;
        }

        std::cout << '\n';
    } while (process);
}

Acc* Server::ProcessAuthorization()
{
    std::string login, pwd;
    std::cout << "Введите логин: ";
    std::cin >> login;
    std::cout << "Введите пароль: ";
    std::cin >> pwd;

    Acc* user = _userRepo.AuthorizeUser (login, pwd);

    if (user == nullptr)
    {
        std::cout << "Ошибка авторизации.\n";
        return nullptr;
    }

    std::cout << "Пользователь авторизован!\n";
    _msgRepo.ViewMessagesForUser (user->getLogin());
    _msgRepo.ViewMessagesForAllUsers();
    return user;
}

void Server::ProcessChat(Acc* user)
{
    std::string text; // Тело сообщения для отправки
    std::string userFrom = user->getLogin();
    std::string userTo;

    _userRepo.UsersList();
    std::cout << "Выберите адресата сообщения: ";
    std::cin >> userTo; // Указываем адресата сообщения
    if (!_userRepo.FindUser (userTo)) // Проверка, что данный адресат существует в сети 
    {
        std::cout << "Адресат c таким именем в сети не зарегистрирован.\n";
        return; // Возвращаемся, чтобы пользователь мог выбрать другого адресата
    }

    std::cout << "Введите сообщение: ";
    std::cin.ignore(); // Очистить буфер ввода перед чтением строки
    std::getline(std::cin, text); // Читаем строку тела сообщения
}
Server::~Server()
{
	//delete _userRepo;
	//delete _msgRepo;
}
*/

#include "Server.h"
#include "UserRepository.h"

Server::Server()
{
    // Initialize as member variables (already declared in Server.h)
}

void Server::MainProcess()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    bool process = true;
    char menuOption;
    do {
        std::cout << "Создать аккаунт введите: 'c'\n";
        std::cout << "Авторизоваться введите:  'a'\n";
        std::cout << "Выход: 'e'\n";
        std::cin >> menuOption;
        switch (menuOption)
        {
        case 'c':
        {
            Acc* newUser = _userRepo.NewUser();
            delete newUser; // Prevent memory leak
            break;
        }
        case 'a':
        {
            Acc* user = ProcessAuthorization();
            if (user == nullptr) {
                std::cout << "Ошибка авторизации. Попробуйте снова.\n";
                continue; // Возвращаемся к началу цикла
            }

            ProcessChat(user);
            delete user; // Prevent memory leak
            break;
        }
        case 'e':
        {
            // Вывод всех зарегистрированных пользователей
            _userRepo.UsersList();
            // Вывод всех отправленных сообщений
            _msgRepo.ViewAllMessages();

            process = false;
            break;
        }
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            break;
        }

        std::cout << '\n';
    } while (process);
}

Acc* Server::ProcessAuthorization()
{
    std::string login, pwd;
    std::cout << "Введите логин: ";
    std::cin >> login;
    std::cout << "Введите пароль: ";
    std::cin >> pwd;

    Acc* user = _userRepo.AuthorizeUser(login, pwd);

    if (user == nullptr)
    {
        std::cout << "Ошибка авторизации.\n";
        return nullptr;
    }

    std::cout << "Пользователь авторизован!\n";
    _msgRepo.ViewMessagesForUser(user->getLogin());
    _msgRepo.ViewMessagesForAllUsers();
    return user;
}

void Server::ProcessChat(Acc* user)
{
    std::string text; // Тело сообщения для отправки
    std::string userFrom = user->getLogin();
    std::string userTo;

    _userRepo.UsersList();
    std::cout << "Выберите адресата сообщения: ";
    std::cin >> userTo; // Указываем адресата сообщения
    
    if (!_userRepo.FindUser(userTo)) // Проверка, что данный адресат существует в сети 
    {
        std::cout << "Адресат c таким именем в сети не зарегистрирован.\n";
        return; // Возвращаемся, чтобы пользователь мог выбрать другого адресата
    }

    std::cout << "Введите сообщение: ";
    std::cin.ignore(); // Очистить буфер ввода перед чтением строки
    std::getline(std::cin, text); // Читаем строку тела сообщения
    
    // FIXED: Actually add the message to the database
    _msgRepo.AddMessage(userFrom, userTo, text);
    std::cout << "Сообщение отправлено!\n";
}

Server::~Server()
{
    // No need to delete anything as we're using composition now
}
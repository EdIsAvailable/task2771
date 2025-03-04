
/*#include "UserRepository.h"
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
*/
#include "UserRepository.h"
#include "db.h" // Подключаем файл с функциями работы с БД
#include <iostream>
#include <stdexcept>
#include <memory> // Для std::unique_ptr

using namespace std;

UserRepository::UserRepository()
{
    // Инициализируем и добавляем первого пользователя в БД для Public Chat
    string login = "ALL", pwd = "example";
    registerUser(login, pwd); // Регистрация пользователя в БД
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
        // Регистрация нового пользователя в БД
        registerUser(login, pwd);

        // Создаем объект Acc для нового пользователя
        Acc* newUser = new Acc(login, pwd, name);
        newUser->Show();

        return newUser;
    }
    catch (const char* c)
    {
        cout << c << endl;
    }
    return nullptr;
}

Acc* UserRepository::FindUser(string login)
{
    // Поиск пользователя в БД
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT Username, PasswordHash FROM Users WHERE Username = ?"
        ));
        pstmt->setString(1, login);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            string username = res->getString("Username");
            string passwordHash = res->getString("PasswordHash");
            return new Acc(username, passwordHash, ""); // Имя можно оставить пустым, если оно не хранится в БД
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
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
    // Для получения количества пользователей в БД можно использовать SQL запрос
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT COUNT(*) FROM Users"
        ));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            return res->getInt(1);
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
    }
    return 0;
}

void UserRepository::UsersList(void)
{
    // Вывод списка пользователей из БД
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT Username FROM Users"
        ));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        cout << "Зарегистрированные пользователи:" << endl;
        while (res->next()) {
            cout << "Login: " << res->getString("Username") << endl;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << " (Error code: " << e.getErrorCode() << ")" << std::endl;
    }
}

UserRepository::~UserRepository()
{
    // В данном случае не нужно освобождать память для пользователей, так как они хранятся в БД
}
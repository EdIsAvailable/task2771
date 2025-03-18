#include "Server.h"
#include "UserRepository.h"

Server::Server()
{
    // Инициализируемся как переменные-члены (уже объявленные в Server.h)
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
            delete user; // Гасим утечку памяти
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
    
    // добавление сообщения в бд
    _msgRepo.AddMessage(userFrom, userTo, text);
    std::cout << "Сообщение отправлено!\n";
}

Server::~Server()
{
    // В принципе, нечего удалять
}
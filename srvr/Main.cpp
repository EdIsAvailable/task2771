#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>
#include "Acc.h"
#include "Socket.h"
#include "Chat.h"
#include "Server.h"
#include "db.h"
#include "NewUser.h"
#include "Logger.h"

using namespace std;

Server* _server;
//Logger* _logger;

// Функция для записи сообщений в лог
void logMessages(Logger& logger, int id) {
    for (int i = 0; i < 5; ++i) {
        logger.writeLog("Thread " + std::to_string(id) + " wrote message " + std::to_string(i));
    }
}



int main()
{

    /*_logger = new Logger();

    // записи в лог
    _logger->writeLog("This is a log message.");

    // чтения из лога
    string logEntry = _logger->readLog();
    cout << "Read log entry: " << logEntry << endl;
*/
   
Logger logger;

    // Создаем несколько потоков для записи в лог
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(logMessages, std::ref(logger), i);
    }

    // Ожидаем завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    // Чтение логов
    try {
        std::string line;
        while (true) {
            line = logger.readLog();
            if (line.empty()) {
                break; // Выход из цикла, если строка пустая
            }
            std::cout << line << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    _server = new Server();
    _server->MainProcess();
   
    delete _server; //  освободить память
    //delete _logger;
    return 0;
}


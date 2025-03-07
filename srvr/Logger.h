/*#pragma once

#include <string>
#include <fstream>
#include <shared_mutex>
#include <mutex>

class Logger {
public:
    Logger(const std::string& filename = "log.txt");
    ~Logger();

    void writeLog(const std::string& message);
    std::string readLog();

private:
    std::string filename_;
    std::fstream file_;
    mutable std::shared_mutex mutex_; // mutable для использования в const методах
};
*/

#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <shared_mutex>

class Logger {
public:
    // Конструктор открывает файл логов
    Logger(const std::string& filename = "log.txt");

    // Деструктор закрывает файл логов
    ~Logger();

    // Метод для записи строки в лог
    void writeLog(const std::string& message);

    // Метод для чтения одной строки из лога
    std::string readLog();

private:
    std::fstream logFile;               // Поток для работы с файлом
    mutable std::shared_mutex mutex_;   // Мьютекс для потокобезопасности
    std::vector<std::string> logLines;  // Вектор для хранения строк лога
    size_t readPosition = 0;           // Текущая позиция чтения
};
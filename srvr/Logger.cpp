#include "Logger.h"
#include <stdexcept>

// Конструктор
Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::in | std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Failed to open log file");
    }
}

// Метод для записи строки в лог
void Logger::writeLog(const std::string& message) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
    else {
        throw std::runtime_error("Log file is not open");
    }
}

// Метод для чтения одной строки из лога
std::string Logger::readLog() {
    std::unique_lock<std::shared_mutex> lock(mutex_);

    // Если файл еще не прочитан, читаем его полностью
    if (logLines.empty() && logFile.is_open()) {
        logFile.seekg(0, std::ios::beg); // Перемещаем указатель в начало файла
        std::string line;
        while (std::getline(logFile, line)) {
            logLines.push_back(line);
        }
    }

    // Возвращаем следующую строку, если она есть
    if (readPosition < logLines.size()) {
        return logLines[readPosition++];
    }
    else {
        readPosition = 0; // Сбрасываем позицию для следующего чтения
        return ""; // Возвращаем пустую строку, если строк больше нет
    }
}

// Деструктор
Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}


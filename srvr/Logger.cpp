#include "Logger.h"
#include <stdexcept>

Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::in | std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        // Если файл не существует, создаем его
        logFile.open(filename, std::ios::out | std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to open or create log file");
        }
        logFile.close();
        logFile.open(filename, std::ios::in | std::ios::out | std::ios::app);
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::writeLog(const std::string& message) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (logFile.is_open()) {
        logFile << message << std::endl;
    } else {
        throw std::runtime_error("Log file is not open");
    }
}


std::string Logger::readLog() {
    std::shared_lock<std::shared_mutex> lock(mutex_);

    if (!logFile.is_open()) {
        throw std::runtime_error("Log file is not open");
    }

    std::string line;
    if (std::getline(logFile, line)) {
        return line;
    } else {
        logFile.clear(); // Сбрасываем флаг ошибки
        logFile.seekg(0, std::ios::beg); // Возвращаем указатель в начало файла
        return ""; // Возвращаем пустую строку, если файл прочитан до конца
    }
}
// Сброс указателя чтения
void Logger::resetReadPosition() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (logFile.is_open()) {
        logFile.clear(); // Сбрасываем флаги ошибок
        logFile.seekg(0, std::ios::beg); // Перемещаем указатель в начало файла
    } else {
        throw std::runtime_error("Log file is not open");
    }
}

// Проверка, достигнут ли конец файла
bool Logger::isEndOfFile() {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return logFile.eof();
}
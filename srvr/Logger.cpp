/*#include "Logger.h"

#include <stdexcept>
#include <iostream>

Logger::Logger(const std::string& filename) 
    : filename_(filename), file_(filename_, std::ios::app) {
    if (!file_.is_open()) {
        throw std::runtime_error("Unable to open log file");
    }
}

Logger::~Logger() {
    if (file_.is_open()) {
        file_.close();
    }
}

void Logger::writeLog(const std::string& message) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (file_.is_open()) {
        file_ << message << std::endl;
    }
}

std::string Logger::readLog() {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    std::string line;
    if (file_.is_open()) {
        std::getline(file_, line);
    }
    return line;
}
    */

    #include "Logger.h"
    #include <stdexcept>
    
    // Конструктор
    Logger::Logger(const std::string& filename) {
        logFile.open(filename, std::ios::in | std::ios::out | std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to open log file");
        }
    }
    
    // Деструктор
    Logger::~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    
    // Метод для записи строки в лог
    void Logger::writeLog(const std::string& message) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        if (logFile.is_open()) {
            logFile << message << std::endl;
        } else {
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
        } else {
            return ""; // Возвращаем пустую строку, если строк больше нет
        }
    }
/*#include "Logger.h"
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
    */

#include "Logger.h"
#include <stdexcept>
#include <iostream>

Logger::Logger(const std::string& filename) {
    // Save filename for potential reopening
    _filename = filename;
    
    // First try to open in read/write/append mode
    logFile.open(filename, std::ios::in | std::ios::out | std::ios::app);
    
    if (!logFile.is_open()) {
        // If file doesn't exist, create it in write mode first
        logFile.clear(); // Clear any error flags
        logFile.open(filename, std::ios::out);
        
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to create log file: " + filename);
        }
        
        // Close and reopen in the desired mode
        logFile.close();
        logFile.open(filename, std::ios::in | std::ios::out | std::ios::app);
        
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to reopen log file after creation: " + filename);
        }
    }
    
    std::cout << "Logger initialized with file: " << filename << std::endl;
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::writeLog(const std::string& message) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    
    // Check if file is still open and in good state
    if (!logFile.is_open() || !logFile.good()) {
        // Try to reopen the file
        if (logFile.is_open()) {
            logFile.close();
        }
        logFile.clear(); // Clear error flags
        logFile.open(_filename, std::ios::in | std::ios::out | std::ios::app);
        
        if (!logFile.is_open() || !logFile.good()) {
            throw std::runtime_error("Failed to write to log file: file is not open or in bad state");
        }
    }
    
    // Get current timestamp
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    struct tm* tm_now = localtime(&now_time_t);
    char timestamp[25];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", tm_now);
    
    // Write timestamped message to log
    logFile << timestamp << message << std::endl;
    
    // Ensure data is written to disk
    logFile.flush();
    
    if (logFile.fail()) {
        throw std::runtime_error("Failed to write to log file: write operation failed");
    }
}

std::string Logger::readLog() {
    std::shared_lock<std::shared_mutex> lock(mutex_);

    if (!logFile.is_open() || !logFile.good()) {
        // Try to reopen the file in read mode
        if (logFile.is_open()) {
            logFile.close();
        }
        logFile.clear(); // Clear error flags
        logFile.open(_filename, std::ios::in | std::ios::out | std::ios::app);
        
        if (!logFile.is_open()) {
            throw std::runtime_error("Log file is not open or in bad state");
        }
    }

    std::string line;
    if (std::getline(logFile, line)) {
        return line;
    } else {
        if (logFile.eof()) {
            return ""; // Reached end of file, return empty string
        } else {
            // Some other error occurred
            throw std::runtime_error("Error reading from log file");
        }
    }
}

void Logger::resetReadPosition() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (logFile.is_open()) {
        logFile.clear(); // Clear any error flags
        logFile.seekg(0, std::ios::beg); // Move read position to beginning of file
    } else {
        throw std::runtime_error("Log file is not open");
    }
}

bool Logger::isEndOfFile() {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return logFile.eof();
}
#include "Logger.h"
#include <stdexcept>
#include <iostream>

Logger::Logger(const std::string& filename) {
    // Сохраняем имя файла для возможного повторного открытия
    _filename = filename;
    
    //  Пробуем открыть файл в режиме чтения/записи/добавления
    logFile.open(filename, std::ios::in | std::ios::out | std::ios::app);
    
    if (!logFile.is_open()) {
        // Если файл не существует, содаём его в режиме записи
        logFile.clear(); // Сбрасываем флаги ошибок
        logFile.open(filename, std::ios::out);
        
        if (!logFile.is_open()) {
            throw std::runtime_error("Не удалось создать файл журнала: " + filename);
        }
        
        // Закроем и снова откроем лог файл в нужном режиме
        logFile.close();
        logFile.open(filename, std::ios::in | std::ios::out | std::ios::app);
        
        if (!logFile.is_open()) {
            throw std::runtime_error("Не удалось повторно открыть файл журнала после создания: " + filename);
        }
    }
    
    std::cout << " Bнициализирован метод Logger c log.txt: " << filename << std::endl;
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::writeLog(const std::string& message) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    
    // Проверяем, открыт ли файл log.txt
    if (!logFile.is_open() || !logFile.good()) {
        // Пробуем снова открыть log
        if (logFile.is_open()) {
            logFile.close();
        }
        logFile.clear(); // Сбрасываем флаги ошибок
        logFile.open(_filename, std::ios::in | std::ios::out | std::ios::app);
        
        if (!logFile.is_open() || !logFile.good()) {
            throw std::runtime_error("Не удалось записать в файл журнала: файл не открыт или ипорчен");
        }
    }
    
    // Получаем актуальную метку времени
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    struct tm* tm_now = localtime(&now_time_t);
    char timestamp[25];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", tm_now);
    
    // Прописываем актуальную метку времени в log
    logFile << timestamp << message << std::endl;
    
    // Убедимся, что данные записаны на диск
    logFile.flush();
    
    if (logFile.fail()) {
        throw std::runtime_error("Не удалось записать в файл журнала: операция завершилась ошибкой");
    }
}

std::string Logger::readLog() {
    std::shared_lock<std::shared_mutex> lock(mutex_);

    if (!logFile.is_open() || !logFile.good()) {
        // открываем файл в режиме чтения
        if (logFile.is_open()) {
            logFile.close();
        }
        logFile.clear(); // Сбрасываем флаги ошибок
        logFile.open(_filename, std::ios::in | std::ios::out | std::ios::app);
        
        if (!logFile.is_open()) {
            throw std::runtime_error("Лог не открывается или испорчен");
        }
    }

    std::string line;
    if (std::getline(logFile, line)) {
        return line;
    } else {
        if (logFile.eof()) {
            return ""; // Достигнут конец файла, возвращаем пустую строку
        } else {
            //  ошибка
            throw std::runtime_error("Ошибка чтения файла журнала");
        }
    }
}

void Logger::resetReadPosition() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (logFile.is_open()) {
        logFile.clear(); // Сбрасываем флаги ошибок
        logFile.seekg(0, std::ios::beg); // Перемещение курсора (указателя?)в начало файла
    } else {
        throw std::runtime_error("Лог не открывается");
    }
}

bool Logger::isEndOfFile() {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return logFile.eof();
}
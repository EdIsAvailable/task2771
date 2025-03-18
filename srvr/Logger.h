#pragma once

#include <fstream>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <ctime>

class Logger {
public:
    Logger(const std::string& filename = "log.txt");
    ~Logger();

    void writeLog(const std::string& message);
    std::string readLog();
    void resetReadPosition(); // Метод для сброса укаателя (курсора)
    bool isEndOfFile();
    
private:
    std::fstream logFile;
    std::string _filename; // Сохраняем имя файля для повторного открытия
    std::shared_mutex mutex_;
};

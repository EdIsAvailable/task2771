
#pragma once

#include <fstream>
#include <string>
#include <mutex>
#include <shared_mutex>

class Logger {
public:
    Logger(const std::string& filename = "log.txt");
    ~Logger();

    void writeLog(const std::string& message);
    std::string readLog();
    void resetReadPosition(); // метод для сброса указателя чтения
    bool isEndOfFile();
    
private:
    std::fstream logFile;
    mutable std::shared_mutex mutex_;
};

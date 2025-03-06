#pragma once

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
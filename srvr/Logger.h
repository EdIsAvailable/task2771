/*#pragma once

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
    std::shared_mutex mutex_;
};
*/

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
    void resetReadPosition(); // Method to reset read position
    bool isEndOfFile();
    
private:
    std::fstream logFile;
    std::string _filename; // Store filename for reopening if necessary
    std::shared_mutex mutex_;
};

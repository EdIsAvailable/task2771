#include "Logger.h"
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
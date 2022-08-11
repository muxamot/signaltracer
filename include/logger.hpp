#pragma once

#include <chrono>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace sgtr
{

enum Loglevel
{
    INFO,
    ERROR,
    WARN
};

class Logger
{
private:
    bool started_{false};

public:
    explicit Logger(Loglevel level)
    {
        switch (level)
        {
        case INFO:
            std::cout << "[INF] ";
            break;
        case ERROR:
            std::cout << "[ERR] ";
            break;
        case WARN:
            std::cout << "[WRN] ";
        default:
            break;
        }

        const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "[" << std::put_time(std::localtime(&time), "%d.%m.%Y %H:%M:%S") << "] ";

        started_ = true;
    }

    ~Logger()
    {
        if (started_)
            std::cout << std::endl;

        started_ = false;
    }

    template <typename T>
    Logger& operator<<(const T& msg)
    {
        std::cout << msg;
        return *this;
    }
};

#define LOG(level) Logger(level) << "[" << std::strrchr("\\" __FILE__, '\\') + 1 << ":" << __LINE__ << "] "

} // namespace sgtr
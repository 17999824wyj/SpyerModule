#pragma once
#include <string>
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>

class UtilGetTime {
public:
    static std::string GetTime()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        // 将时间转换为字符串
        std::stringstream ss;
#ifdef _WIN32
        std::tm timeInfo = { 0 };
        localtime_s(&timeInfo, &currentTime);
        ss << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");
#else
        ss << std::put_time(std::localtime(&currentTime), "%Y-%m-%d %H:%M:%S");
#endif
        return ss.str();
    }
};
#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <time.h>
#include <experimental/source_location>
#include "LogLevel.hpp"

namespace irt
{

using Loc = std::experimental::source_location;

#define LogInst (irt::Logger::getInst())

class Logger
{
public:
    static Logger& initInst();
    static Logger& getInst();
    static void destroyInst();
    // function
    void setLogVerbose(int log_verbose);
    void openLogFileStream(std::string log_file_path);
    void closeLogFileStream();

    template <typename T, typename... Args>
    void info(Loc location, const T &value, const Args &...args)
    {
        if (_log_verbose > 0)
        {
            return;
        }
        printLog(LogLevel::kInfo, location, value, args...);
    }

    template <typename T, typename... Args>
    void warning(Loc location, const T &value, const Args &...args)
    {
        if (_log_verbose > 1)
        {
            return;
        }
        printLog(LogLevel::kWarning, location, value, args...);
    }

    template <typename T, typename... Args>
    void error(Loc location, const T &value, const Args &...args)
    {
        printLog(LogLevel::kError, location, value, args...);
        closeLogFileStream();
        exit(0);
    }

private:
    // self
    static Logger *_log_instance;
    // config & database
    int _log_verbose = 0;
    std::ofstream *_log_file = nullptr;
    size_t _temp_storage_size = 1024;
    std::vector<std::string> _temp_storage;

    Logger() { _temp_storage.reserve(_temp_storage_size); };
    Logger(const Logger &other) = delete;
    Logger(Logger &&other) = delete;
    ~Logger() { closeLogFileStream(); }
    Logger &operator=(const Logger &other) = delete;
    Logger &operator=(Logger &&other) = delete;
    // function
    // function
    template <typename T, typename... Args>
    void printLog(LogLevel log_level, Loc location, const T &value, const Args &...args)
    {
        const char *log_color_start;
        const char *log_level_char;

        switch (log_level)
        {
        case LogLevel::kInfo:
            log_color_start = "\033[1;34m";
            log_level_char = "Info";
            break;
        case LogLevel::kWarning:
            log_color_start = "\033[1;33m";
            log_level_char = "Warning";
            break;
        case LogLevel::kError:
            log_color_start = "\033[1;31m";
            log_level_char = "Error";
            break;
        default:
            log_color_start = "\033[1;32m";
            log_level_char = "Info";
            break;
        }
        const char *log_color_end = "\033[0m";

        std::string file_name = std::filesystem::absolute(getString(location.file_name(), ":", location.line()));
        file_name.erase(remove(file_name.begin(), file_name.end(), '\"'), file_name.end());
        if (log_level != LogLevel::kError)
        {
            std::string::size_type iPos = file_name.find_last_of('/') + 1;
            file_name = file_name.substr(iPos, file_name.length() - iPos);
        }
        std::string header = getString("[RT ", getTimestamp(), " ", file_name, " func:", location.function_name(), " ");
        std::string message = getString(value, args...);

        std::string origin_log = getString(header, log_level_char, "] ", message, "\n");
        std::string color_log = getString(header, log_color_start, log_level_char, log_color_end, "] ", message, "\n");

        if (_log_file != nullptr)
        {
            if (!_temp_storage.empty())
            {
                for (std::string &origin_log : _temp_storage)
                {
                    pushStream(*_log_file, origin_log);
                }
                _temp_storage.clear();
            }
            pushStream(*_log_file, origin_log);
        }
        else
        {
            if (_temp_storage.size() >= _temp_storage_size)
            {
                _temp_storage.clear();
            }
            _temp_storage.push_back(origin_log);
        }
        pushStream(std::cout, color_log);
    }

    template <typename T, typename... Args>
    std::string getString(T value, Args... args)
    {
        std::stringstream oss;
        pushStream(oss, value, args...);
        std::string string = oss.str();
        oss.clear();
        return string;
    }

    template <typename Stream, typename T, typename... Args>
    void pushStream(Stream &stream, T t, const Args &...args)
    {
        stream << t;
        pushStream(stream, args...);
        return;
    }

    template <typename Stream, typename T>
    void pushStream(Stream &stream, T t)
    {
        stream << t;
    }

    char *getTimestamp()
    {
        time_t now = time(nullptr);
        tm *t = localtime(&now);
        char *buffer = new char[32];
        strftime(buffer, 32, "%Y/%m/%d %H:%M:%S", t);
        return buffer;
    }
};
}
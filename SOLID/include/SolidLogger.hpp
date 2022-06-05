#pragma once

#include <string>
#include <vector>

#include "SolidUtils.hpp"

enum LogLevel {
    INFO,
    WARNING,
    ERROR,
    FATAL
};

struct LogEntry {
    const char* message;
    const char* details;
    const char* file;
    int* line;
    std::string timestamp;
    LogLevel level;
};

class SolidLogger {
public:
    void Log(const char* message, const char* details, const char* file, int* line, LogLevel level);

    std::vector<LogEntry> GetLogs() { return mLogs; }
    void ClearLogs() { mLogs.clear(); }
    void PauseLogging() { mLoggingPaused = true; }
    void ResumeLogging() { mLoggingPaused = false; }
    bool IsLoggingPaused() { return mLoggingPaused; }

    unsigned int GetInfoCount() { return GetInfos().size(); }
    unsigned int GetWarningCount() { return GetWarnings().size(); }
    unsigned int GetErrorCount() { return GetErrors().size(); }
    unsigned int GetFatalCount() { return GetFatals().size(); }

    std::vector<LogEntry> GetErrors();
    std::vector<LogEntry> GetWarnings();
    std::vector<LogEntry> GetInfos();
    std::vector<LogEntry> GetFatals();
    std::vector<LogEntry> Search(const char* query);

private:
    std::vector<LogEntry> mLogs;
    bool mLoggingPaused = false;
};
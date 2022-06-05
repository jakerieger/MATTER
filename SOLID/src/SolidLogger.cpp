#include "SolidLogger.hpp"

void SolidLogger::Log(const char* message, const char* details, const char* file, int* line, LogLevel level) {
    LogEntry entry;
    entry.message = message;
    entry.details = details;
    entry.timestamp = SolidUtils::GetTimestamp();
    entry.file = file;
    entry.line = line;
    entry.level = level;

    if (!mLoggingPaused) {
        mLogs.push_back(entry);
    }
}

std::vector<LogEntry> SolidLogger::GetInfos() {
    std::vector<LogEntry> infos;

    for (auto& log : mLogs) {
        if (log.level == INFO) {
            infos.push_back(log);
        }
    }

    return infos;
}

std::vector<LogEntry> SolidLogger::GetWarnings() {
    std::vector<LogEntry> warnings;

    for (auto& log : mLogs) {
        if (log.level == WARNING) {
            warnings.push_back(log);
        }
    }

    return warnings;
}

std::vector<LogEntry> SolidLogger::GetErrors() {
    std::vector<LogEntry> errors;

    for (auto& log : mLogs) {
        if (log.level == ERROR) {
            errors.push_back(log);
        }
    }

    return errors;
}

std::vector<LogEntry> SolidLogger::GetFatals() {
    std::vector<LogEntry> fatals;

    for (auto& log : mLogs) {
        if (log.level == FATAL) {
            fatals.push_back(log);
        }
    }

    return fatals;
}

std::vector<LogEntry> SolidLogger::Search(const char* query) {
    std::vector<LogEntry> results;

    for (auto& log : mLogs) {
        if (strstr(log.message, query) != nullptr) {
            results.push_back(log);
        }
    }

    return results;
}
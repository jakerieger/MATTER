/** Copyright 2022 Jake Rieger
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
        if (log.level == LogLevel_INFO) {
            infos.push_back(log);
        }
    }

    return infos;
}

std::vector<LogEntry> SolidLogger::GetWarnings() {
    std::vector<LogEntry> warnings;

    for (auto& log : mLogs) {
        if (log.level == LogLevel_WARNING) {
            warnings.push_back(log);
        }
    }

    return warnings;
}

std::vector<LogEntry> SolidLogger::GetErrors() {
    std::vector<LogEntry> errors;

    for (auto& log : mLogs) {
        if (log.level == LogLevel_ERROR) {
            errors.push_back(log);
        }
    }

    return errors;
}

std::vector<LogEntry> SolidLogger::GetFatals() {
    std::vector<LogEntry> fatals;

    for (auto& log : mLogs) {
        if (log.level == LogLevel_FATAL) {
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

std::shared_ptr<SolidLogger> SolidLogger::GetInstance() {
    static std::shared_ptr<SolidLogger> instance{new SolidLogger};
    return instance;
}
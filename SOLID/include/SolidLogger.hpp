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

#pragma once

#include <string>
#include <vector>

#include "SolidUtils.hpp"

enum LogLevel {
    LogLevel_INFO,
    LogLevel_WARNING,
    LogLevel_ERROR,
    LogLevel_FATAL
};

struct LogEntry {
    const char* message; ///< The message displayed in the console
    const char* details; ///< The details displayed in the console when the user selects the entry
    const char* file; ///< The file the log entry originated from
    int* line; ///< The line the log entry originated from
    std::string timestamp; ///< The timestamp of the log entry
    LogLevel level; ///< The level of the log entry
};

/**
 * @brief Handles logging functionality for the editor console
 * 
 * @note I've implemented the logger as a singleton to make it easy to access from anywhere in the codebase.
 * This is generally a bad idea, but in this case it's fine because the logger is used globally by the
 * whole system and should only ever exist as one instance.
 * 
 * @author Jake Rieger
 */
class SolidLogger {
public:
    /**
     * @brief Log a message to the console
     * 
     * @param message The message to log
     * @param details The message details
     * @param file The file the message originated from
     * @param line The line the message originated from
     * @param level The level of the message
     */
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

    /**
     * @brief Singleton accessor
     * 
     * Based on the implementation found here: https://stackoverflow.com/a/40337728
     */
    SolidLogger(SolidLogger const&) = delete;
    SolidLogger& operator=(SolidLogger const&) = delete;
    static std::shared_ptr<SolidLogger> GetInstance();

private:
    std::vector<LogEntry> mLogs;
    bool mLoggingPaused = false;

    SolidLogger() {}
};
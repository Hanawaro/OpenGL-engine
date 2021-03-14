#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

namespace System {

    // SandBox messages
    struct LogError;
    struct LogWarning;
    struct LogMessage;
    struct LogSucsess;
    // System messages
    struct LogSystemError;
    struct LogSystemWarning;
    struct LogSystemMessage;
    struct LogSystemSucsess;

    static struct LogPush {} end;

    class Logger {
    public:
        enum class GlobalMode {
            OnlySystem,
            OnlySandbox,
            AllStuff
        };
        enum class LocaleMode {
            None,
            Message,
            Error,
            Warning,
            Sucsess,
            All
        };
        
        enum class RealTimeGlobalMode {
            SystemMode,
            SandboxMode
        };
        enum class RealTimeLocaleMode {
            Message,
            Error,
            Warning,
            Sucsess
        };
        
    public:
        // operators
        Logger& operator<<(int data);
        Logger& operator<<(unsigned int data);
        Logger& operator<<(long data);
        Logger& operator<<(unsigned long data);
        Logger& operator<<(long long data);
        Logger& operator<<(unsigned long long data);
        Logger& operator<<(float data);
        Logger& operator<<(double data);
        Logger& operator<<(long double data);
        Logger& operator<<(const std::string& data);
        
        // controllers
        Logger& operator<<(const LogPush& push);
        
        Logger& operator<<(const LogMessage& lcl);
        Logger& operator<<(const LogError& lcl);
        Logger& operator<<(const LogWarning& lcl);
        Logger& operator<<(const LogSucsess& lcl);
        
        Logger& operator<<(const LogSystemMessage& lcl);
        Logger& operator<<(const LogSystemError& lcl);
        Logger& operator<<(const LogSystemWarning& lcl);
        Logger& operator<<(const LogSystemSucsess& lcl);
        
        // getters
        GlobalMode GetGlobaleMode(void) const { return m_GlobalMode; }
        LocaleMode GetLocaleMode(void) const { return m_LocaleMode; }
        // setters
        void SetGlobaleMode(GlobalMode mode) { m_GlobalMode = mode; }
        void SetLocaleMode(LocaleMode mode) { m_LocaleMode = mode; }
    private:
        template <typename Type>
        void LoadData(const Type& data, std::function<std::string(const Type& tmp)> func) {

            if (m_LocaleMode == LocaleMode::None) return; // optimize function
            
            if (m_Buffer.size()) {
                switch (m_RealTimeLocaleMode) {
                    case RealTimeLocaleMode::Message:
                        if ((int)RealTimeLocaleMode::Message + 1 <= (int)m_LocaleMode)
                            m_Buffer += func(data);
                        break;
                    case RealTimeLocaleMode::Error:
                        if ((int)RealTimeLocaleMode::Error + 1 <= (int)m_LocaleMode)
                            m_Buffer += std::string("\x1b[31m") + func(data) + "\x1b[0m";
                        break;
                    case RealTimeLocaleMode::Warning:
                        if ((int)RealTimeLocaleMode::Warning + 1 <= (int)m_LocaleMode)
                            m_Buffer += std::string("\x1b[33m") + func(data) + "\x1b[0m";
                        break;
                    case RealTimeLocaleMode::Sucsess:
                        if ((int)RealTimeLocaleMode::Sucsess + 1 <= (int)m_LocaleMode)
                            m_Buffer += std::string("\x1b[32m") + func(data) + "\x1b[0m";
                        break;
                }
                return;
            }
            
            char timeBuffer[255] = { 0 };
            time_t seconds = time(NULL);
            tm* timeinfo = localtime(&seconds);
            strftime(timeBuffer, 80, "[%H:%M:%S]", timeinfo);
            
            if ((int) m_RealTimeGlobalMode == (int) m_GlobalMode || m_GlobalMode == GlobalMode::AllStuff) {
                switch (m_RealTimeLocaleMode) {
                    case RealTimeLocaleMode::Message:
                        if ((int)RealTimeLocaleMode::Message + 1 <= (int)m_LocaleMode) {
                            // code this
                            if (m_RealTimeGlobalMode == RealTimeGlobalMode::SandboxMode)
                                m_Buffer += std::string(timeBuffer) + " Sandbox: " + func(data);
                            else if (m_RealTimeGlobalMode == RealTimeGlobalMode::SystemMode)
                                m_Buffer += std::string(timeBuffer) + " System:  " + func(data);
                        }
                        break;
                    case RealTimeLocaleMode::Error:
                        if ((int)RealTimeLocaleMode::Error + 1 <= (int)m_LocaleMode) {
                            // code this
                            if (m_RealTimeGlobalMode == RealTimeGlobalMode::SandboxMode)
                                m_Buffer += std::string("\x1b[31m") + timeBuffer + " Sandbox: " + func(data) + "\x1b[0m";
                            else if (m_RealTimeGlobalMode == RealTimeGlobalMode::SystemMode)
                                m_Buffer += std::string("\x1b[31m") + timeBuffer + " System:  " + func(data) + "\x1b[0m";
                        }
                        break;
                    case RealTimeLocaleMode::Warning:
                        if ((int)RealTimeLocaleMode::Warning + 1 <= (int)m_LocaleMode) {
                            // code this
                            if (m_RealTimeGlobalMode == RealTimeGlobalMode::SandboxMode)
                                m_Buffer += std::string("\x1b[33m") + timeBuffer + " Sandbox: " + func(data) + "\x1b[0m";
                            else if (m_RealTimeGlobalMode == RealTimeGlobalMode::SystemMode)
                                m_Buffer += std::string("\x1b[33m") + timeBuffer + " System:  " + func(data) + "\x1b[0m";
                        }
                        break;
                    case RealTimeLocaleMode::Sucsess:
                        if ((int)RealTimeLocaleMode::Sucsess + 1 <= (int)m_LocaleMode) {
                            // code this
                            if (m_RealTimeGlobalMode == RealTimeGlobalMode::SandboxMode)
                                m_Buffer += std::string("\x1b[32m") + timeBuffer + " Sandbox: " + func(data) + "\x1b[0m";
                            else if (m_RealTimeGlobalMode == RealTimeGlobalMode::SystemMode)
                                m_Buffer += std::string("\x1b[32m") + timeBuffer + " System:  " + func(data) + "\x1b[0m";
                        }
                        break;
                }
            }
        }
    public:
        RealTimeGlobalMode m_RealTimeGlobalMode = RealTimeGlobalMode::SystemMode;
        RealTimeLocaleMode m_RealTimeLocaleMode = RealTimeLocaleMode::Sucsess;
        
        GlobalMode m_GlobalMode = GlobalMode::AllStuff;
        LocaleMode m_LocaleMode = LocaleMode::Sucsess;
        
        std::string m_Buffer = "";
    };

    extern Logger log;

    // sandbox messages
    static struct LogMessage {
        template <typename Type>
        Logger& operator<<(const Type& data) {
            return log << LogMessage() << data;
        }
    } msg;

    static struct LogError   {
        template <typename Type>
        Logger& operator<<(const Type& data) {
            return log << LogError() << data;
        }
    } err;

    static struct LogWarning {
        template <typename Type>
        Logger& operator<<(const Type& data) {
            return log << LogWarning() << data;
        }
    } wrn;

    static struct LogSucsess {
        template <typename Type>
        Logger& operator<<(const Type& data) {
            return log << LogSucsess() << data;
        }
    } scs;
    // system messages
    static struct LogSystemMessage {
        template <typename Type>
        Logger& operator<<(const Type& data) {
            return log << LogSystemMessage() << data;
        }
    } _msg;
    
    static struct LogSystemError   {
        template <typename Type>
        Logger& operator<<(const Type& data) {
            return log << LogSystemError() << data;
        }
    } _err;

    static struct LogSystemWarning {
        template <typename Type>
        Logger& operator<<(const Type& data) {
            return log << LogSystemWarning() << data;
        }
    } _wrn;

    static struct LogSystemSucsess {
        template <typename Type>
        Logger& operator<<(const Type& data) {
            return log << LogSystemSucsess() << data;
        }
    } _scs;
}

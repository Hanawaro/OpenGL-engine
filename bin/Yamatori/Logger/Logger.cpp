#include <ymtpch.hpp>
#include "Logger.hpp"

namespace System {

    Logger log;
    
    Logger& Logger::operator<<(int data) {
        LoadData<int>(data, [](const int& tmp) -> std::string { return std::to_string(tmp); });
        return *this;
    }

    Logger& Logger::operator<<(unsigned int data) {
        LoadData<unsigned int>(data, [](const unsigned int& tmp) -> std::string { return std::to_string(tmp); });
        return *this;
    }

    Logger& Logger::operator<<(long data) {
        LoadData<long>(data, [](const long& tmp) -> std::string { return std::to_string(tmp); });
        return *this;
    }

    Logger& Logger::operator<<(unsigned long data) {
        LoadData<unsigned long>(data, [](const unsigned long& tmp) -> std::string { return std::to_string(tmp); });
        return *this;
    }

    Logger& Logger::operator<<(long long data) {
        LoadData<long long>(data, [](const long long& tmp) -> std::string { return std::to_string(tmp); });
        return *this;
    }

    Logger& Logger::operator<<(unsigned long long data) {
        LoadData<unsigned long long>(data, [](const unsigned long long& tmp) -> std::string { return std::to_string(tmp); });
        return *this;
    }

    Logger& Logger::operator<<(float data) {
        LoadData<float>(data, [](const float& tmp) -> std::string { return std::to_string(tmp); });
        return *this;
    }

    Logger& Logger::operator<<(double data) {
        LoadData<double>(data, [](const double& tmp) -> std::string { return std::to_string(tmp); });
        return *this;
    }

    Logger& Logger::operator<<(long double data) {
        LoadData<long double>(data, [](const long double& tmp) -> std::string { return std::to_string(tmp); });
        return *this;
    }

    Logger& Logger::operator<<(const std::string& data) {
        LoadData<std::string>(data, [](const std::string& tmp) -> std::string { return tmp; });
        return *this;
    }
    
    // controllers
    Logger& Logger::operator<<(const LogPush& push) {
        if (m_Buffer.size())
            std::cout << m_Buffer << std::endl;
        m_Buffer.clear();
        return *this;
    }
    
    Logger& Logger::operator<<(const LogMessage& lcl) {
        if (m_Buffer.size()) {
            std::cout << m_Buffer << std::endl;
            m_Buffer.clear();
        }
        m_RealTimeLocaleMode = RealTimeLocaleMode::Message;
        m_RealTimeGlobalMode = RealTimeGlobalMode::SandboxMode;
        return *this;
    }

    Logger& Logger::operator<<(const LogError& lcl) {
        if (m_Buffer.size()) {
            std::cout << m_Buffer << std::endl;
            m_Buffer.clear();
        }
        m_RealTimeLocaleMode = RealTimeLocaleMode::Error;
        m_RealTimeGlobalMode = RealTimeGlobalMode::SandboxMode;
        return *this;
    }

    Logger& Logger::operator<<(const LogWarning& lcl) {
        if (m_Buffer.size()) {
            std::cout << m_Buffer << std::endl;
            m_Buffer.clear();
        }
        m_RealTimeLocaleMode = RealTimeLocaleMode::Warning;
        m_RealTimeGlobalMode = RealTimeGlobalMode::SandboxMode;
        return *this;
    }
    Logger& Logger::operator<<(const LogSucsess& lcl) {
        if (m_Buffer.size()) {
            std::cout << m_Buffer << std::endl;
            m_Buffer.clear();
        }
        m_RealTimeLocaleMode = RealTimeLocaleMode::Sucsess;
        m_RealTimeGlobalMode = RealTimeGlobalMode::SandboxMode;
        return *this;
    }
    
    Logger& Logger::operator<<(const LogSystemMessage& lcl) {
        if (m_Buffer.size()) {
            std::cout << m_Buffer << std::endl;
            m_Buffer.clear();
        }
        m_RealTimeLocaleMode = RealTimeLocaleMode::Message;
        m_RealTimeGlobalMode = RealTimeGlobalMode::SystemMode;
        return *this;
    }

    Logger& Logger::operator<<(const LogSystemError& lcl)  {
        if (m_Buffer.size()) {
            std::cout << m_Buffer << std::endl;
            m_Buffer.clear();
        }
        m_RealTimeLocaleMode = RealTimeLocaleMode::Error;
        m_RealTimeGlobalMode = RealTimeGlobalMode::SystemMode;
        return *this;
    }

    Logger& Logger::operator<<(const LogSystemWarning& lcl) {
        if (m_Buffer.size()) {
            std::cout << m_Buffer << std::endl;
            m_Buffer.clear();
        }
        m_RealTimeLocaleMode = RealTimeLocaleMode::Warning;
        m_RealTimeGlobalMode = RealTimeGlobalMode::SystemMode;
        return *this;
    }

    Logger& Logger::operator<<(const LogSystemSucsess& lcl) {
        if (m_Buffer.size()) {
            std::cout << m_Buffer << std::endl;
            m_Buffer.clear();
        }
        m_RealTimeLocaleMode = RealTimeLocaleMode::Sucsess;
        m_RealTimeGlobalMode = RealTimeGlobalMode::SystemMode;
        return *this;
    }
    
}

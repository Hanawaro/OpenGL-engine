#pragma once

#include <Yamatori/Logger/Logger.hpp>

namespace System { namespace Object {

    class ConfigReader {
    public:
        ConfigReader(void) = delete;
        ConfigReader(const ConfigReader&) = delete;
        ConfigReader& operator=(const ConfigReader&) = delete;
        
        static bool Read(const std::string& path, uint32_t parameters, uint32_t arguments, const std::string& limiter = "=", const std::string& enumeration = ",", const std::string& comment = "#", const std::string& merger = "\"");
        static bool Read(std::ifstream& cfg, uint32_t parameters, uint32_t arguments, const std::string& limiter = "=", const std::string& enumeration = ",", const std::string& comment = "#", const std::string& merger = "\"");
        
        static bool GetParameter(uint32_t parameterID, std::vector<std::string>& parameter);
        static bool GetParameter(const std::string& parameterValue, std::vector<std::string>& parameter);
        
        static bool GetArgument(uint32_t parameter_id, uint32_t argumentID, std::string& argument);
        static bool GetArgument(const std::string& parameterValue, uint32_t argumentID, std::string& argument);
        
        static inline const std::vector<std::vector<std::string>>& GetCfg(void) { return m_Data; }
    private:
        static std::vector<std::string> ParseLine(const std::string& line, const std::string& limiter, const std::string& enumeration, const std::string& comment, const std::string& merger);
    private:
        static std::vector<std::vector<std::string>> m_Data;
    };

} }

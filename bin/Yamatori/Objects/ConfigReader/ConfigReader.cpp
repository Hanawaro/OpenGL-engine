#include <ymtpch.hpp>
#include "ConfigReader.hpp"

namespace System {  namespace Object {

    std::vector<std::vector<std::string>> ConfigReader::m_Data;

    bool ConfigReader::Read(const std::string& path, uint32_t parameters, uint32_t arguments, const std::string& limiter, const std::string& enumeration, const std::string& comment, const std::string& merger) {
        
        if (!path.size()) {
            _err << "Name of config file is empty" << end;
            return false;
        }
        std::ifstream cfg(path);
        bool isSucsess = Read(cfg, parameters, arguments, limiter, enumeration, comment, merger);
        cfg.close();
        
        return isSucsess;
    }

    bool ConfigReader::Read(std::ifstream& cfg, uint32_t parameters, uint32_t arguments, const std::string& limiter, const std::string& enumeration, const std::string& comment, const std::string& merger) {
        
        if (cfg.is_open()) {
            std::string parameterValue;
            while (getline(cfg, parameterValue)) {
                auto commentIndex = parameterValue.find(comment);
                if ( commentIndex != std::string::npos) {
                    parameterValue.resize(commentIndex);
                }
                
                if (parameterValue.size()) {
                    std::vector<std::string> argumentsValue = ParseLine(parameterValue, limiter, enumeration, comment, merger);
                    
                    std::vector<std::string> push_parameter;
                    uint32_t amountOfArguments = 0;
                    for (const auto& arg : argumentsValue) {
                        if (arg.size()) {
                            if (amountOfArguments <= arguments) {
                                push_parameter.push_back(arg);
                                amountOfArguments++;
                            } else {
                                _wrn << "Too many arguments of " << argumentsValue[0] << " parameter" << end;
                            }
                        }
                    }
                    for (uint32_t i = amountOfArguments; i < arguments; i++) {
                        push_parameter.push_back("");
                    }
                    m_Data.push_back(push_parameter);
                }
            }
        } else {
            _err << "Could not open the config file" << end;
            return false;
        }
        return true;
    }

    bool ConfigReader::GetParameter(uint32_t parameterID, std::vector<std::string>& parameter) {
        if (parameterID >= m_Data.size()) {
            _err << "Array out of bounds" << end;
            return false;
        } else {
            parameter = m_Data[parameterID];
            return true;
        }
    }

    bool ConfigReader::GetParameter(const std::string& parameterValue, std::vector<std::string>& parameter) {
        std::string tmpParameterValue = parameterValue;
        std::transform(tmpParameterValue.begin(), tmpParameterValue.end(), tmpParameterValue.begin(), ::tolower);
        for (const auto& parameterVec : m_Data) {
            if (parameterVec[0] == tmpParameterValue) {
                parameter = parameterVec;
                return true;
            }
        }
        _wrn << "No such parameter \"" << parameterValue << "\"" << end;
        return false;
    }

    bool ConfigReader::GetArgument(uint32_t parameterID, uint32_t argumentID, std::string& argument) {
        std::vector<std::string> parameter;
        if (!GetParameter(parameterID, parameter))
            return false;
        
        if (argumentID >= m_Data[parameterID].size()) {
            _err << "Array out of bounds" << end;
            return false;
        }
        if (argumentID == 0) {
            _wrn << "Take the name of parameter \"" << m_Data[parameterID][0] << "\"" << end;
        }
        argument = m_Data[parameterID][argumentID];
        return true;
    }

    bool ConfigReader::GetArgument(const std::string& parameterValue, uint32_t argumentID, std::string& argument) {
        std::string tmpParameterValue = parameterValue;
        std::transform(tmpParameterValue.begin(), tmpParameterValue.end(), tmpParameterValue.begin(), ::tolower);
        for (const auto& parameter : m_Data) {
            if (parameter[0] == tmpParameterValue) {
                if (argumentID >= parameter.size()) {
                    _err << "Array out of bounds" << end;
                    return false;
                }
                if (argumentID == 0) {
                    _wrn << "Take the name of parameter \"" << parameter[0] << "\"" << end;
                }
                argument = parameter[argumentID];
                return true;
            }
        }
        _wrn << "No such parameter \"" << parameterValue << "\"" << end;
        return "";
    }
    
    std::vector<std::string> ConfigReader::ParseLine(const std::string& line, const std::string& limiter, const std::string& enumeration, const std::string& comment, const std::string& merger) {
        std::vector<std::string> dataResult;
        std::string tmpData = "";
        char realtimeMerger = '\0';
        bool hasLimiter = false;
        for (char ch : line) {
            if (limiter.find(ch) != std::string::npos && !hasLimiter) {
                if (tmpData.size()) {
                    std::transform(tmpData.begin(), tmpData.end(), tmpData.begin(), ::tolower);
                    dataResult.push_back(tmpData);
                    tmpData.clear();
                    hasLimiter = true;
                } else {
                    break;
                }
            } else if (enumeration.find(ch) != std::string::npos && realtimeMerger == '\0') {
                if (tmpData.size()) {
                    dataResult.push_back(tmpData);
                    tmpData.clear();
                }
            } else if (merger.find(ch) != std::string::npos && realtimeMerger == '\0') {
                if (tmpData.size()) {
                    dataResult.push_back(tmpData);
                    tmpData.clear();
                }
                realtimeMerger = ch;
            } else if (merger.find(ch) != std::string::npos && realtimeMerger != '\0') {
                if (tmpData.size()) {
                    dataResult.push_back(tmpData);
                    tmpData.clear();
                }
                realtimeMerger = '\0';
            } else if (comment.find(ch) != std::string::npos && realtimeMerger == '\0') {
                if (tmpData.size()) {
                    dataResult.push_back(tmpData);
                    tmpData.clear();
                }
                break;
            } else if ((ch == ' ' || ch == '\t') && realtimeMerger == '\0') { } else {
                tmpData += ch;
            }
        }
        if (tmpData.size())
            dataResult.push_back(tmpData);
        
        return dataResult;
    }

} }

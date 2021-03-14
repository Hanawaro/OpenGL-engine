#pragma once

#include <Yamatori/Core/Window/WindowProps.hpp>
#include <Yamatori/Objects/ConfigReader/ConfigReader.hpp>

namespace System { namespace Object {

    class ConfigSetter {
    public:
        ConfigSetter(void) = delete;
        ConfigSetter(const ConfigSetter&) = delete;
        ConfigSetter& operator=(const ConfigSetter&) = delete;
        
        static void SetProperties(void);
    private:
        static void SetWindowProp(const std::string name, bool (*func)(const std::string&, bool) ) {
            std::string argument;
            if (Object::ConfigReader::GetArgument(name, 1, argument)) {
                if (func(argument, true)) {
                    _wrn << "\"" << name << "\" parameter not correct, set by default" << end;
                } else if (!argument.size())
                    _wrn << "Window " << name << " is empty" << end;
            } else {
                func(argument, true);
                _wrn << "\"" << name << "\" parameter not found, set by default" << end;
            }
        }
    };

} }

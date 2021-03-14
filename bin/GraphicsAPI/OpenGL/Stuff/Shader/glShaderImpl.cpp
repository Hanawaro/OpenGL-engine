#include <ymtpch.hpp>
#include "glShaderImpl.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace System { namespace GL { namespace Impl {

    static uint32_t ShaderTypeFromString(const std::string& tag) {
        if (tag == "vertex")
            return 0;
        else if (tag == "fragment")
            return 1;
        _err << "No such shader's tag" << end;
        return 0;
    }
    
    Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc ) {
        CompileShader(name, vertexSrc, fragmentSrc);
    }
    
    Shader::Shader(const std::string& filePath) {
        std::string shaders[static_cast<int>(TypeShader::Count)];
        
        std::string name = filePath;
        auto lastSlah = name.find_last_of("\\/");
        name = name.substr(lastSlah == std::string::npos ? 0 : lastSlah + 1);
        auto lastDot = name.rfind(".");
        name = name.substr(0, lastDot == std::string::npos ? name.size() - 1 : lastDot);
        
        auto file = ReadFile(filePath);
        
        const std::string tag = "#type";
        unsigned long pos = file.find(tag, 0);
        while (pos != std::string::npos) {
            size_t eol = file.find_first_of("\r\n", pos);
                        
            size_t begin = pos + tag.size() + 1;
            std::string type = file.substr(begin, eol - begin);
            

            size_t nextLinePos = file.find_first_not_of("\r\n", eol);
            pos = file.find(tag, nextLinePos);
            shaders[ShaderTypeFromString(type)] = file.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? file.size() - 1 : nextLinePos));
        }
        
        CompileShader(name, shaders[static_cast<int>(TypeShader::Vertex)], shaders[static_cast<int>(TypeShader::Fragment)]);
    }

    Shader::~Shader(void) {
        glDeleteProgram(m_RendererID);
    }
    
    void Shader::SetUniform1f(const std::string& name, const glm::fvec1& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, uniform.x);
    }
    
    void Shader::SetUniform2f(const std::string& name, const glm::fvec2& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, uniform.x, uniform.y);
    }
    
    void Shader::SetUniform3f(const std::string& name, const glm::fvec3& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, uniform.x, uniform.y, uniform.z);
    }
    
    void Shader::SetUniform4f(const std::string& name, const glm::fvec4& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, uniform.x, uniform.y, uniform.z, uniform.w);
    }
    
    void Shader::SetUniform1fv(const std::string& name, const glm::fvec1* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1fv(location, (GLsizei)count, (GLfloat*)uniform);
    }
    
    void Shader::SetUniform2fv(const std::string& name, const glm::fvec2* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2fv(location, (GLsizei)count, (GLfloat*)uniform);
    }
    
    void Shader::SetUniform3fv(const std::string& name, const glm::fvec3* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3fv(location, (GLsizei)count, (GLfloat*)uniform);
    }
    
    void Shader::SetUniform4fv(const std::string& name, const glm::fvec4* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4fv(location, (GLsizei)count, (GLfloat*)uniform);
    }
    
    
    void Shader::SetUniform1i(const std::string& name, const glm::ivec1& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, uniform.x);
    }
    
    void Shader::SetUniform2i(const std::string& name, const glm::ivec2& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2i(location, uniform.x, uniform.y);
    }
    
    void Shader::SetUniform3i(const std::string& name, const glm::ivec3& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3i(location, uniform.x, uniform.y, uniform.z);
    }
    
    void Shader::SetUniform4i(const std::string& name, const glm::ivec4& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4i(location, uniform.x, uniform.y, uniform.z, uniform.w);
    }
    
    void Shader::SetUniform1iv(const std::string& name, const glm::ivec1* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1iv(location, (GLsizei)count, (GLint*)uniform);
    }
    
    void Shader::SetUniform2iv(const std::string& name, const glm::ivec2* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2iv(location, (GLsizei)count, (GLint*)uniform);
    }
    
    void Shader::SetUniform3iv(const std::string& name, const glm::ivec3* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3iv(location, (GLsizei)count, (GLint*)uniform);
    }
    
    void Shader::SetUniform4iv(const std::string& name, const glm::ivec4* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4iv(location, (GLsizei)count, (GLint*)uniform);
    }
    
    
    void Shader::SetUniform1ui(const std::string& name, const glm::uvec1& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1ui(location, uniform.x);
    }
    
    void Shader::SetUniform2ui(const std::string& name, const glm::uvec2& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2ui(location, uniform.x, uniform.y);
    }
    
    void Shader::SetUniform3ui(const std::string& name, const glm::uvec3& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3ui(location, uniform.x, uniform.y, uniform.z);
    }
    
    void Shader::SetUniform4ui(const std::string& name, const glm::uvec4& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4ui(location, uniform.x, uniform.y, uniform.z, uniform.w);
    }
    
    void Shader::SetUniform1uiv(const std::string& name, const glm::uvec1* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1uiv(location, (GLsizei)count, (GLuint*)uniform);
    }
    
    void Shader::SetUniform2uiv(const std::string& name, const glm::uvec2* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2uiv(location, (GLsizei)count, (GLuint*)uniform);
    }
    
    void Shader::SetUniform3uiv(const std::string& name, const glm::uvec3* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3uiv(location, (GLsizei)count, (GLuint*)uniform);
    }
    
    void Shader::SetUniform4uiv(const std::string& name, const glm::uvec4* uniform, size_t count) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4uiv(location, (GLsizei)count, (GLuint*)uniform);
    }
    
    
    void Shader::SetUniformMat2(const std::string& name, const glm::mat2& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }
    
    void Shader::SetUniformMat3(const std::string& name, const glm::mat3& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }
    
    void Shader::SetUniformMat4(const std::string& name, const glm::mat4& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }
    
    void Shader::SetUniformMat2x3(const std::string& name, const glm::mat2x3& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }
    
    void Shader::SetUniformMat3x2(const std::string& name, const glm::mat3x2& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }
    
    
    void Shader::SetUniformMat2x4(const std::string& name, const glm::mat2x4& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }
    
    void Shader::SetUniformMat4x2(const std::string& name, const glm::mat4x2& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }
    
    void Shader::SetUniformMat3x4(const std::string& name, const glm::mat3x4& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }
    
    void Shader::SetUniformMat4x3(const std::string& name, const glm::mat4x3& uniform) const {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
    }

    void Shader::CompileShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(vertexShader);

            _err << infoLog.data() << end;
            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            _err << infoLog.data() << end;
            return;
        }

        m_RendererID = glCreateProgram();
        GLuint program = m_RendererID;

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            
            _err << infoLog.data() << end;
            return;
        }

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }
    
    std::string Shader::ReadFile(const std::string& path) {
        std::string result;
        std::ifstream in(path);
        
        if (in.is_open()) {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        } else {
            _err << "Could not read shader file" << end;
        }
        
        return result;
    }
    
} } }

#pragma once

#include "ShaderInterface.hpp"

namespace System {

    class Shader {
    public:
        Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        Shader(const std::string& filePath);
        ~Shader(void);
        
        inline void Bind(void) const { m_Instance->Bind(); }
        inline void UnBind(void) const { m_Instance->UnBind(); }
        
        inline void SetUniform1f(const std::string& name, const glm::fvec1& uniform) const { m_Instance->SetUniform1f(name, uniform); }
        inline void SetUniform2f(const std::string& name, const glm::fvec2& uniform) const { m_Instance->SetUniform2f(name, uniform); }
        inline void SetUniform3f(const std::string& name, const glm::fvec3& uniform) const { m_Instance->SetUniform3f(name, uniform); }
        inline void SetUniform4f(const std::string& name, const glm::fvec4& uniform) const { m_Instance->SetUniform4f(name, uniform); }
        
        inline void SetUniform1fv(const std::string& name, const glm::fvec1* uniform, size_t count) const { m_Instance->SetUniform1fv(name, uniform, count); }
        inline void SetUniform2fv(const std::string& name, const glm::fvec2* uniform, size_t count) const { m_Instance->SetUniform2fv(name, uniform, count); }
        inline void SetUniform3fv(const std::string& name, const glm::fvec3* uniform, size_t count) const { m_Instance->SetUniform3fv(name, uniform, count); }
        inline void SetUniform4fv(const std::string& name, const glm::fvec4* uniform, size_t count) const { m_Instance->SetUniform4fv(name, uniform, count); }
        
        
        inline void SetUniform1i(const std::string& name, const glm::ivec1& uniform) const { m_Instance->SetUniform1i(name, uniform); }
        inline void SetUniform2i(const std::string& name, const glm::ivec2& uniform) const { m_Instance->SetUniform2i(name, uniform); }
        inline void SetUniform3i(const std::string& name, const glm::ivec3& uniform) const { m_Instance->SetUniform3i(name, uniform); }
        inline void SetUniform4i(const std::string& name, const glm::ivec4& uniform) const { m_Instance->SetUniform4i(name, uniform); }
        
        inline void SetUniform1iv(const std::string& name, const glm::ivec1* uniform, size_t count) const { m_Instance->SetUniform1iv(name, uniform, count); }
        inline void SetUniform2iv(const std::string& name, const glm::ivec2* uniform, size_t count) const { m_Instance->SetUniform2iv(name, uniform, count); }
        inline void SetUniform3iv(const std::string& name, const glm::ivec3* uniform, size_t count) const { m_Instance->SetUniform3iv(name, uniform, count); }
        inline void SetUniform4iv(const std::string& name, const glm::ivec4* uniform, size_t count) const { m_Instance->SetUniform4iv(name, uniform, count); }
        
        
        inline void SetUniform1ui(const std::string& name, const glm::uvec1& uniform) const  { m_Instance->SetUniform1ui(name, uniform); }
        inline void SetUniform2ui(const std::string& name, const glm::uvec2& uniform) const  { m_Instance->SetUniform2ui(name, uniform); }
        inline void SetUniform3ui(const std::string& name, const glm::uvec3& uniform) const  { m_Instance->SetUniform3ui(name, uniform); }
        inline void SetUniform4ui(const std::string& name, const glm::uvec4& uniform) const  { m_Instance->SetUniform4ui(name, uniform); }
        
        inline void SetUniform1uiv(const std::string& name, const glm::uvec1* uniform, size_t count) const  { m_Instance->SetUniform1uiv(name, uniform, count); }
        inline void SetUniform2uiv(const std::string& name, const glm::uvec2* uniform, size_t count) const  { m_Instance->SetUniform2uiv(name, uniform, count); }
        inline void SetUniform3uiv(const std::string& name, const glm::uvec3* uniform, size_t count) const  { m_Instance->SetUniform3uiv(name, uniform, count); }
        inline void SetUniform4uiv(const std::string& name, const glm::uvec4* uniform, size_t count) const  { m_Instance->SetUniform4uiv(name, uniform, count); }
        
        
        inline void SetUniformMat2(const std::string& name, const glm::mat2& uniform) const { m_Instance->SetUniformMat2(name, uniform); }
        inline void SetUniformMat3(const std::string& name, const glm::mat3& uniform) const { m_Instance->SetUniformMat3(name, uniform); }
        inline void SetUniformMat4(const std::string& name, const glm::mat4& uniform) const { m_Instance->SetUniformMat4(name, uniform); }

        inline void SetUniformMat2x3(const std::string& name, const glm::mat2x3& uniform) const { m_Instance->SetUniformMat2x3(name, uniform); }
        inline void SetUniformMat3x2(const std::string& name, const glm::mat3x2& uniform) const { m_Instance->SetUniformMat3x2(name, uniform); }
        
        inline void SetUniformMat2x4(const std::string& name, const glm::mat2x4& uniform) const { m_Instance->SetUniformMat2x4(name, uniform); }
        inline void SetUniformMat4x2(const std::string& name, const glm::mat4x2& uniform) const { m_Instance->SetUniformMat4x2(name, uniform); }
        
        inline void SetUniformMat3x4(const std::string& name, const glm::mat3x4& uniform) const { m_Instance->SetUniformMat3x4(name, uniform); }
        inline void SetUniformMat4x3(const std::string& name, const glm::mat4x3& uniform) const { m_Instance->SetUniformMat4x3(name, uniform); }
        
        inline uint32_t GetRendererID(void) const { return m_Instance->GetRendererID(); }
    private:
        Interface::Shader* m_Instance;
    };

}

#pragma once

#include <glm/glm.hpp>

namespace System { namespace Interface {

    class Shader {
    public:
        Shader(void) = default;
        virtual ~Shader(void) = default;
        
        virtual inline void Bind(void) const = 0;
        virtual inline void UnBind(void) const = 0;
        
        virtual void SetUniform1f(const std::string& name, const glm::fvec1& uniform) const = 0;
        virtual void SetUniform2f(const std::string& name, const glm::fvec2& uniform) const = 0;
        virtual void SetUniform3f(const std::string& name, const glm::fvec3& uniform) const = 0;
        virtual void SetUniform4f(const std::string& name, const glm::fvec4& uniform) const = 0;
        
        virtual void SetUniform1fv(const std::string& name, const glm::fvec1* uniform, size_t count) const = 0;
        virtual void SetUniform2fv(const std::string& name, const glm::fvec2* uniform, size_t count) const = 0;
        virtual void SetUniform3fv(const std::string& name, const glm::fvec3* uniform, size_t count) const = 0;
        virtual void SetUniform4fv(const std::string& name, const glm::fvec4* uniform, size_t count) const = 0;
        
        virtual void SetUniform1i(const std::string& name, const glm::ivec1& uniform) const = 0;
        virtual void SetUniform2i(const std::string& name, const glm::ivec2& uniform) const = 0;
        virtual void SetUniform3i(const std::string& name, const glm::ivec3& uniform) const = 0;
        virtual void SetUniform4i(const std::string& name, const glm::ivec4& uniform) const = 0;
        
        virtual void SetUniform1iv(const std::string& name, const glm::ivec1* uniform, size_t count) const = 0;
        virtual void SetUniform2iv(const std::string& name, const glm::ivec2* uniform, size_t count) const = 0;
        virtual void SetUniform3iv(const std::string& name, const glm::ivec3* uniform, size_t count) const = 0;
        virtual void SetUniform4iv(const std::string& name, const glm::ivec4* uniform, size_t count) const = 0;
        
        virtual void SetUniform1ui(const std::string& name, const glm::uvec1& uniform) const  = 0;
        virtual void SetUniform2ui(const std::string& name, const glm::uvec2& uniform) const  = 0;
        virtual void SetUniform3ui(const std::string& name, const glm::uvec3& uniform) const  = 0;
        virtual void SetUniform4ui(const std::string& name, const glm::uvec4& uniform) const  = 0;
        
        virtual void SetUniform1uiv(const std::string& name, const glm::uvec1* uniform, size_t count) const  = 0;
        virtual void SetUniform2uiv(const std::string& name, const glm::uvec2* uniform, size_t count) const  = 0;
        virtual void SetUniform3uiv(const std::string& name, const glm::uvec3* uniform, size_t count) const  = 0;
        virtual void SetUniform4uiv(const std::string& name, const glm::uvec4* uniform, size_t count) const  = 0;
        
        virtual void SetUniformMat2(const std::string& name, const glm::mat2& uniform) const = 0;
        virtual void SetUniformMat3(const std::string& name, const glm::mat3& uniform) const = 0;
        virtual void SetUniformMat4(const std::string& name, const glm::mat4& uniform) const = 0;
        
        virtual void SetUniformMat2x3(const std::string& name, const glm::mat2x3& uniform) const = 0;
        virtual void SetUniformMat3x2(const std::string& name, const glm::mat3x2& uniform) const = 0;
        
        virtual void SetUniformMat2x4(const std::string& name, const glm::mat2x4& uniform) const = 0;
        virtual void SetUniformMat4x2(const std::string& name, const glm::mat4x2& uniform) const = 0;
        
        virtual void SetUniformMat3x4(const std::string& name, const glm::mat3x4& uniform) const = 0;
        virtual void SetUniformMat4x3(const std::string& name, const glm::mat4x3& uniform) const = 0;
        
        virtual inline uint32_t GetRendererID(void) const = 0;
    };

} }

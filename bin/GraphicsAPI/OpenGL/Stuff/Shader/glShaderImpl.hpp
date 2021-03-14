#pragma once

#include <Yamatori/Logger/Logger.hpp>
#include <Yamatori/Core/Renderer/Shader/ShaderInterface.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace System { namespace GL { namespace Impl {

    class Shader final : public Interface::Shader {
    public:
        Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        Shader(const std::string& filePath);
        virtual ~Shader(void);
        
        virtual inline void Bind(void) const override { glUseProgram(m_RendererID); }
        virtual inline void UnBind(void) const override { glUseProgram(0); }
        
        virtual void SetUniform1f(const std::string& name, const glm::fvec1& uniform) const override;
        virtual void SetUniform2f(const std::string& name, const glm::fvec2& uniform) const override;
        virtual void SetUniform3f(const std::string& name, const glm::fvec3& uniform) const override;
        virtual void SetUniform4f(const std::string& name, const glm::fvec4& uniform) const override;
        
        virtual void SetUniform1fv(const std::string& name, const glm::fvec1* uniform, size_t count) const override;
        virtual void SetUniform2fv(const std::string& name, const glm::fvec2* uniform, size_t count) const override;
        virtual void SetUniform3fv(const std::string& name, const glm::fvec3* uniform, size_t count) const override;
        virtual void SetUniform4fv(const std::string& name, const glm::fvec4* uniform, size_t count) const override;
        
        virtual void SetUniform1i(const std::string& name, const glm::ivec1& uniform) const override;
        virtual void SetUniform2i(const std::string& name, const glm::ivec2& uniform) const override;
        virtual void SetUniform3i(const std::string& name, const glm::ivec3& uniform) const override;
        virtual void SetUniform4i(const std::string& name, const glm::ivec4& uniform) const override;
        
        virtual void SetUniform1iv(const std::string& name, const glm::ivec1* uniform, size_t count) const override;
        virtual void SetUniform2iv(const std::string& name, const glm::ivec2* uniform, size_t count) const override;
        virtual void SetUniform3iv(const std::string& name, const glm::ivec3* uniform, size_t count) const override;
        virtual void SetUniform4iv(const std::string& name, const glm::ivec4* uniform, size_t count) const override;
        
        virtual void SetUniform1ui(const std::string& name, const glm::uvec1& uniform) const override;
        virtual void SetUniform2ui(const std::string& name, const glm::uvec2& uniform) const override;
        virtual void SetUniform3ui(const std::string& name, const glm::uvec3& uniform) const override;
        virtual void SetUniform4ui(const std::string& name, const glm::uvec4& uniform) const override;
        
        virtual void SetUniform1uiv(const std::string& name, const glm::uvec1* uniform, size_t count) const override;
        virtual void SetUniform2uiv(const std::string& name, const glm::uvec2* uniform, size_t count) const override;
        virtual void SetUniform3uiv(const std::string& name, const glm::uvec3* uniform, size_t count) const override;
        virtual void SetUniform4uiv(const std::string& name, const glm::uvec4* uniform, size_t count) const override;
        
        virtual void SetUniformMat2(const std::string& name, const glm::mat2& uniform) const override;
        virtual void SetUniformMat3(const std::string& name, const glm::mat3& uniform) const override;
        virtual void SetUniformMat4(const std::string& name, const glm::mat4& uniform) const override;
        
        virtual void SetUniformMat2x3(const std::string& name, const glm::mat2x3& uniform) const override;
        virtual void SetUniformMat3x2(const std::string& name, const glm::mat3x2& uniform) const override;
        
        virtual void SetUniformMat2x4(const std::string& name, const glm::mat2x4& uniform) const override;
        virtual void SetUniformMat4x2(const std::string& name, const glm::mat4x2& uniform) const override;
        
        virtual void SetUniformMat3x4(const std::string& name, const glm::mat3x4& uniform) const override;
        virtual void SetUniformMat4x3(const std::string& name, const glm::mat4x3& uniform) const override;
        
        virtual inline uint32_t GetRendererID(void) const override { return m_RendererID; }
    private:
        void CompileShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        std::string ReadFile(const std::string& path);
    private:
        enum class TypeShader {
            Vertex,
            Fragment,
            Count
        };
    private:
        uint32_t m_RendererID;
        std::string m_Name;
    };

} } }

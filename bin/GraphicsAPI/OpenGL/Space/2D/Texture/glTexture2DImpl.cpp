#include <ymtpch.hpp>
#include "glTexture2DImpl.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stb_image/stb_image.h>

namespace System { namespace GL { namespace Impl {
    
    Texture2D::Texture2D(const std::string& path) {
        SetTexture(path);
    }
    
    Texture2D::Texture2D(uint32_t width, uint32_t height) : m_Size(width, height) {
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_Size.first, m_Size.second);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Size.first, m_Size.second, GL_RGBA8, GL_UNSIGNED_BYTE, nullptr);
    }
    
    Texture2D::Texture2D(void* data, uint32_t width, uint32_t height, size_t size) : m_Size(width, height) {
        
        unsigned int internalFormat = 0, dataFormat = 0;
        
        switch (size / (width * height)) {
            case 4:
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
                break;
            case 3:
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
                break;
            default:
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
                _err << "Only 3 and 4 channels are supported" << end;
                break;
        }
        
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexStorage2D(GL_TEXTURE_2D, 1, (GLenum) internalFormat, m_Size.first, m_Size.second);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Size.first, m_Size.second, (GLenum) dataFormat, GL_UNSIGNED_BYTE, data);
    }
    
    void Texture2D::SetTexture(const std::string& path) {
        
        m_Path = path;
        
        int channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), (int*)&m_Size.first, (int*)&m_Size.second, &channels, 0);
        if (!data) {
            _err << "Could not create the texture \"" << path << "\"" << end;
            m_Size = {0, 0};
            return;
        }
        
        unsigned int internalFormat = 0, dataFormat = 0;
        
        switch (channels) {
            case 4:
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
                break;
            case 3:
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
                break;
            default:
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
                _err << "Only 3 and 4 channels are supported" << end;
                break;
        }
        
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexStorage2D(GL_TEXTURE_2D, 1, (GLenum) internalFormat, m_Size.first, m_Size.second);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Size.first, m_Size.second, (GLenum) dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    
    void Texture2D::SetData(void* data, size_t size) {
        unsigned long channels = size / (m_Size.first * m_Size.second);
        unsigned int internalFormat = 0, dataFormat = 0;
        
        switch (channels) {
            case 4:
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
                break;
            case 3:
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
                break;
            default:
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
                _err << "Only 3 and 4 channels are supported" << end;
                break;
        }
        
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, m_Size.first, m_Size.second);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Size.first, m_Size.second, dataFormat, GL_UNSIGNED_BYTE, data);
    }
    
    void Texture2D::Bind(int slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }
    
    void Texture2D::UnBind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
} } }

#pragma once

#include <Yamatori/Logger/Logger.hpp>

namespace System {

    struct ShaderDataType {
    public:
        enum Data {
            None = 0,
            Float, Float2, Float3, Float4,
            Int, Int2, Int3, Int4,
            Bool,
            Mat3, Mat4
        };
    public:
        ShaderDataType(Data data = None) : m_Data(data) {}
        ~ShaderDataType(void) = default;
        
        operator Data() const { return m_Data; }
    
        static uint32_t ToBaseType(const ShaderDataType& data);
        static uint32_t GetSize(const ShaderDataType& data);
    private:
        Data m_Data;
    };

    class BufferElement {
    public:
        std::string Name;
        uint32_t Size;
        ShaderDataType Type;
        uintptr_t Offset;
        bool Normalized;
    public:
        BufferElement(const std::string& name, ShaderDataType::Data type, bool normilized = false)
            : Name(name), Size(ShaderDataType::GetSize(type)), Type(type), Offset(0), Normalized(normilized) {}
    
        uint32_t GetComponentCount(void) const;
    };

    class BufferLayout {
    public:
        BufferLayout(void) {}
        BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Buffer(elements) {
            CalculateOffsetsAndStride();
        }
        virtual ~BufferLayout(void) = default;
        
        inline uint32_t GetStride(void) const { return m_Stride; }
        inline const  std::vector<BufferElement>& GetElements(void) const { return m_Buffer; }
        
        std::vector<BufferElement>::iterator begin() { return m_Buffer.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Buffer.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Buffer.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Buffer.end(); }
    private:
        void CalculateOffsetsAndStride() {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Buffer) {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }
    private:
        std::vector<BufferElement> m_Buffer;
        uint32_t m_Stride = 0;
    };

}

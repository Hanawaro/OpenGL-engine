#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace System {

    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        virtual ~OrthographicCamera(void) = default;
        
        void SetProjection(float left, float right, float bottom, float top);
        
        inline void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
        inline const glm::vec3& GetPosition(void) const { return m_Position; }
        
        inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
        inline float GetRotation(void) const { return m_Rotation; }
        
        inline const glm::mat4& GetViewMatrix(void) const { return m_ViewMatrix; }
        inline const glm::mat4& GetProjectionMatrix(void) const { return m_ProjectionMatrix; }
        inline const glm::mat4& GetViewProjectionMatrix(void) const { return m_ViewProjectionMatrix; }
    private:
        void RecalculateViewMatrix(void);
    private:
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;
        
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        float m_Rotation = 0.0f;
    };

}

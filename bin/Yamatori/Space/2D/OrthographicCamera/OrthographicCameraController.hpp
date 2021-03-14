#pragma once

#include "OrthographicCamera.hpp"
#include <Yamatori/Core/Event/Input/Input.hpp>

namespace System {
    
    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);
        
        void OnUpdate(double time);
        void OnEvent(Event& event);
        
        void OnResize(float width, float height);
        
        inline OrthographicCamera& get(void) { return m_Camera; }
        inline const OrthographicCamera& get(void) const { return m_Camera; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& event);
        bool OnWindowResized(WindowResizeEvent& event);
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0;
        
        OrthographicCamera m_Camera;
        
        bool m_Rotation;
        
        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f;
        
        glm::vec3 m_CameraTranslationSpeed = { 2.0f, 2.0f, 0.0f };
        glm::vec3 m_CameraRotationSpeed = { 0.0f, 0.0f, 30.0f };
    };
    
}

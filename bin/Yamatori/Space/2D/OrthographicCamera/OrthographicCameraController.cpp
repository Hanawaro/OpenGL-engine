#include "OrthographicCameraController.hpp"

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace System {
    
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation) {}
    
    void OrthographicCameraController::OnUpdate(double time) {
        glm::vec3 pos = m_Camera.GetPosition();
        glm::vec3 vec = { 0.0f, 0.0f, 0.0f };
        float rot = m_Camera.GetRotation();

        if (Input::IsKeyPressed(GL::Key::W)) { vec.y += m_CameraTranslationSpeed.x * time; }
        if (Input::IsKeyPressed(GL::Key::S)) { vec.y -= m_CameraTranslationSpeed.x * time; }
        if (Input::IsKeyPressed(GL::Key::A)) { vec.x -= m_CameraTranslationSpeed.y * time; }
        if (Input::IsKeyPressed(GL::Key::D)) { vec.x += m_CameraTranslationSpeed.y * time; }
        
        if (m_Rotation) {
            if (Input::IsKeyPressed(GL::Key::Q)) { rot += m_CameraRotationSpeed.z * time; }
            if (Input::IsKeyPressed(GL::Key::E)) { rot -= m_CameraRotationSpeed.z * time; }

            if (rot > 360.0f || rot < -360.0f) rot = 0;

            vec = glm::rotate(vec, glm::radians(rot), glm::vec3(0, 0, 1));

            m_Camera.SetRotation(rot);
        }
        pos += vec;
        m_Camera.SetPosition(pos);
        
        m_CameraTranslationSpeed = { m_ZoomLevel, m_ZoomLevel, m_ZoomLevel };
    }
    
    void OrthographicCameraController::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        
        dispatcher.dispatch<MouseScrolledEvent>(std::bind(&OrthographicCameraController::OnMouseScrolled, this, std::placeholders::_1));
        dispatcher.dispatch<WindowResizeEvent>(std::bind(&OrthographicCameraController::OnWindowResized, this, std::placeholders::_1));
    }
    
    void OrthographicCameraController::OnResize(float width, float height) {
        m_AspectRatio = width / height;
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    }
    
    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event) {
        m_ZoomLevel += event.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
//        m_ZoomLevel = std::min(m_ZoomLevel, 5.0f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
    
    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event) {
        OnResize(event.GetWidth(), event.GetHeight());
        return false;
    }
    
    
    
    
}

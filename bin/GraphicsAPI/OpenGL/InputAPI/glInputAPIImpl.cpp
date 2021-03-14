#include <ymtpch.hpp>
#include "glInputAPIImpl.hpp"

#include <Yamatori/Application.hpp>

namespace System { namespace GL { namespace Impl {

    bool InputAPI::IsKeyPressed(unsigned int keycode) const {
        auto window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow()->GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool InputAPI::IsMouseButtonPressed(unsigned int button) const {
        auto window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow()->GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    std::pair<float, float> InputAPI::GetMousePosition(void) const {
        auto window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow()->GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { (float)xpos, (float)ypos };
    }

    float InputAPI::GetMouseX(void) const { return GetMousePosition().first; }

    float InputAPI::GetMouseY(void) const { return GetMousePosition().second; }

} } }

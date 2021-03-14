#include <ymtpch.hpp>
#include "glfImGuiLayerImpl.hpp"

#include <Yamatori/Logger/Logger.hpp>
#include <Yamatori/Application.hpp>
#include <Yamatori/Core/Window/Window.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ImGui/imgui.h>
#include <ImGui/examples/imgui_impl_glfw.h>
#include <ImGui/examples/imgui_impl_opengl3.h>

namespace System { namespace GL { namespace Impl {

    void ImGuiLayer::AttachImpl(void) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        
        ImGui::StyleColorsDark();
        
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        
        io.IniFilename = "assets/cfg/imgui.ini";
        
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow()->GetNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::DetachImpl(void) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    
    void ImGuiLayer::BeginImpl(void) const {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::EndImpl(void) const {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)WindowProps::width, (float)WindowProps::height);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
    
    void ImGuiLayer::HandleEventImpl(Event& event) {
        if (m_IsBlock) {
            ImGuiIO& io = ImGui::GetIO();
            event.Handled |= event.IsInCatagory(EventCategoryMouse) & io.WantCaptureMouse;
            event.Handled |= event.IsInCatagory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
        
        // delete
        if(Input::IsKeyPressed(GL::Key::Space)) {
            Application::EndApplication();
            return;
        }
        // delete
    }

} } }

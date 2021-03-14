#pragma once

#include "Yamatori/Application.hpp"

extern System::Application* System::CreateApplication(void);

int main(int argc, char** argv) {
    
    system("clear");
    
    auto app = System::CreateApplication();
    app->SetWindowProps();
    app->SetLoggerProps();
    app->Init();
    app->InitImpl();
    
    app->Run();
    
    delete app;
}

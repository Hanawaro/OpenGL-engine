#include "GLEW.hpp"

namespace System {
    
    bool GLEW::s_IsInit = false;
    
    void GLEW::Init(void) {
        if (s_IsInit) return;
        glewExperimental = GL_TRUE;
        glewInit();
        s_IsInit = true;
    }
    
}

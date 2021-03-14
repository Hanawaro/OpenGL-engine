#pragma once

#include <GL/glew.h>

namespace System {
    
    class GLEW {
    public:
        GLEW(void) = delete;
        GLEW(const GLEW&) = delete;
        GLEW& operator=(const GLEW&) = delete;
        
        static void Init(void);
    private:
        static bool s_IsInit;
    };
    
}

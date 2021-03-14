#pragma once

namespace System {
    
    struct Specification {
        uint32_t Width = 0, Height = 0;
        uint32_t Sample = 1;
        
        bool SwapChainTarget = false;
    };
    
}

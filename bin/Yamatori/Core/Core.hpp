#pragma once

#include <Yamatori/Logger/Logger.hpp>

namespace System {

    template <typename Type>
    using Scope = std::unique_ptr<Type>;

    template <typename Type>
    using Ref = std::shared_ptr<Type>;

#if defined(__APPLE__) || defined(__APPLE_CC__) || defined(__OSX__)
    static double s_Scale = 2.0;
#else
    static double s_Scale = 1.0;
#endif
    
}

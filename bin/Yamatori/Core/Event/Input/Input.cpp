#include <ymtpch.hpp>
#include "Input.hpp"

namespace System {

    Ref<InputAPI> Input::s_Instance = Ref<InputAPI>( new InputAPI() );

}

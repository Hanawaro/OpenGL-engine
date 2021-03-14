#pragma once

#include "TimeUnits.hpp"

#include <chrono>
#include <thread>

namespace System { namespace Object {

    class Timer {
    public:
        Timer(void);
        ~Timer(void) = default;
        
        void Start(void);
        void Restart(void);
        void Pause(void);
        void Continue(void);
        void Stop(void);
        
        TimeUnit DeltaTime(void);
        TimeUnit CurrentTime(void) const;
        
        inline bool IsRunning(void) const { return m_Running; }
        inline bool IsPaused(void) const { return m_Paused; }
    private:
        std::chrono::time_point<std::chrono::system_clock> m_StartTime;
        std::chrono::time_point<std::chrono::system_clock> m_PauseTime;
        std::chrono::time_point<std::chrono::system_clock> m_StopTime;
        
        std::chrono::duration<double, std::milli> m_DuratinPause;
        std::chrono::duration<double, std::milli> m_Delta;
        
        bool m_Running;
        bool m_Paused;
        bool m_WasPaused;
    };

} }

#include <ymtpch.hpp>
#include "Timer.hpp"

#include <Yamatori/Logger/Logger.hpp>

namespace System { namespace Object {

    Timer::Timer(void) : m_Running(false), m_Paused(false), m_WasPaused(false) {}
        
    void Timer::Start(void) {
        if (m_Running) return;
        
        m_Running = true;
        m_Paused = false;
        m_WasPaused = false;
        
        m_StartTime = m_StopTime = std::chrono::system_clock::now();
        m_DuratinPause = std::chrono::microseconds(0);
    }
    
    void Timer::Restart(void) {
        Stop();
        Start();
    }
    
    void Timer::Pause(void) {
        if (!m_Running || m_Paused) return;
        
        m_Running = false;
        m_Paused = true;
        m_WasPaused = true;
        
        m_PauseTime = std::chrono::system_clock::now();
        m_DuratinPause = std::chrono::milliseconds(0);
    }
    
    void Timer::Continue(void) {
        if (!m_Paused || m_Running) return;

        m_Running = true;
        m_Paused  = false;
        m_WasPaused = true;

        m_DuratinPause = std::chrono::system_clock::now() - m_PauseTime;
    }
    
    void Timer::Stop(void) {
        if (!m_Running) return;
        m_StopTime = std::chrono::system_clock::now();
        m_Running = false;
        m_Paused = false;
    }
    
    TimeUnit Timer::DeltaTime(void) {
        if (m_WasPaused)
            m_DuratinPause = std::chrono::system_clock::now() - m_PauseTime;
        else
            m_DuratinPause = std::chrono::milliseconds(0);
        
        if (m_Running || m_Paused)
            m_Delta = std::chrono::system_clock::now() - m_StartTime - m_DuratinPause;
        else
            m_Delta = m_StopTime - m_StartTime - m_DuratinPause;

        return m_Delta.count();
    }

} }

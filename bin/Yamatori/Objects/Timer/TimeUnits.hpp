#pragma once

namespace System { namespace Object {

    struct TimeUnit {
    public:
        TimeUnit(float t = 0.0f) : time(t) {}
        ~TimeUnit(void) = default;
        
        inline float ToMilliSeconds(void) const { return time; }
        inline float ToSeconds(void) const { return ToMilliSeconds() / 1000.0f; }
        inline float ToMinutes(void) const { return ToSeconds() / 60.0f; }
        inline float ToHour(void) const { return ToMinutes() / 60.0f; }
        
        inline void SetTime(float t) { time = t; }
        inline float GetTime(void) const { return time; }
    private:
        float time;
    };

} }

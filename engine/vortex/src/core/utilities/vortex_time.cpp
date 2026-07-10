#include "vortex/core/utilities/vortex_time.hpp"
#include <chrono>

namespace vortex::utils
{
    static std::chrono::time_point<std::chrono::high_resolution_clock> s_startTime;
    static std::chrono::time_point<std::chrono::high_resolution_clock> s_lastTime;

    double VxTime::s_deltaTime = 0.0;
    double VxTime::s_unscaledDeltaTime = 0.0;
    double VxTime::s_gameTime = 0.0;
    double VxTime::s_realTime = 0.0;
    double VxTime::s_timeScale = 1.0;

    void VxTime::init()
    {
        s_startTime = std::chrono::high_resolution_clock::now();
        s_lastTime = s_startTime;
    }

    void VxTime::update()
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt_duration = now - s_lastTime;
        s_lastTime = now;

        s_unscaledDeltaTime = dt_duration.count();
        
        // AAA Safety: Cap delta time to prevent the "Spiral of Death"
        // if the user drags the window or the OS freezes the thread.
        if (s_unscaledDeltaTime > 0.25) 
        {
            s_unscaledDeltaTime = 0.25;
        }

        s_deltaTime = s_unscaledDeltaTime * s_timeScale;

        s_realTime += s_unscaledDeltaTime;
        s_gameTime += s_deltaTime;
    }

    double VxTime::getDeltaTime() { return s_deltaTime; }
    double VxTime::getUnscaledDeltaTime() { return s_unscaledDeltaTime; }
    double VxTime::getGameTime() { return s_gameTime; }
    double VxTime::getRealTime() { return s_realTime; }
    
    void VxTime::setTimeScale(double scale) { s_timeScale = scale; }
    double VxTime::getTimeScale() { return s_timeScale; }
}

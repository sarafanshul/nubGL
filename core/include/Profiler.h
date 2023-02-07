//
// Created by Anshul Saraf on 08/02/23.
//

#ifndef OPENGLBASICS_PROFILER_H
#define OPENGLBASICS_PROFILER_H

#include <unordered_map>

class Timer {
public:
    Timer() {
        Reset();
    }

    void Reset() {
        m_Start = std::chrono::high_resolution_clock::now();
    }

    float Elapsed() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
    }

    float ElapsedMillis() {
        return Elapsed() * 1000.0f;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
};

class PerformanceProfiler {
public:
    void SetPerFrameTiming(const char* name, float time) {
        if ( m_PerFrameData.find(name) == m_PerFrameData.end())
            m_PerFrameData[ name ] = 0.0f;

        m_PerFrameData[ name ] += time;
    }

    void Clear() { m_PerFrameData.clear(); }

    [[nodiscard]] const std::unordered_map<const char*, float>& GetPerFrameData() const { return m_PerFrameData; }

private:
    std::unordered_map<const char*, float> m_PerFrameData;
};

class ScopePerfTimer {
public:
    ScopePerfTimer(const char* name, PerformanceProfiler* profiler)
            : m_Name(name), m_Profiler(profiler) {}

    ~ScopePerfTimer() {
        if ( m_Profiler ) {
            float time = m_Timer.ElapsedMillis();
            m_Profiler->SetPerFrameTiming(m_Name, time);
        }
    }

private:
    const char* m_Name;
    PerformanceProfiler* m_Profiler;
    Timer m_Timer;
};

class Profiler {
public:
    static PerformanceProfiler* m_PerformanceProfile;
};

#define PROFILE(name) ScopePerfTimer timer__LINE__(name, Profiler::m_PerformanceProfile)


#endif //OPENGLBASICS_PROFILER_H

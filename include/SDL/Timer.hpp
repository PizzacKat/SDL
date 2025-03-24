#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

namespace SDL {
    typedef std::chrono::high_resolution_clock Clock;
    typedef Clock::time_point TimePoint;

    class TimeSpan {
    public:
        TimeSpan(TimePoint startTime, TimePoint endTime);

        [[nodiscard]] TimePoint GetStart() const;
        [[nodiscard]] TimePoint GetEnd() const;

        [[nodiscard]] float AsSeconds() const;
        [[nodiscard]] std::size_t AsMilliseconds() const;
        [[nodiscard]] std::size_t AsMicroseconds() const;
    private:
        TimePoint _start;
        TimePoint _end;
    };

    class Timer {
    public:
        Timer();

        void Start();
        TimeSpan Restart();
        TimeSpan Reset();
        [[nodiscard]] TimeSpan GetElapsed() const;
        TimeSpan Stop();
    private:
        bool _started;
        TimePoint _start;
        TimePoint _end;
    };
}

#endif //TIMER_HPP

#include "SDL/Timer.hpp"

namespace SDL {
    TimeSpan::TimeSpan(const TimePoint startTime, const TimePoint endTime): _start(startTime), _end(endTime) {

    }

    TimePoint TimeSpan::GetStart() const {
        return _start;
    }

    TimePoint TimeSpan::GetEnd() const {
        return _end;
    }

    float TimeSpan::AsSeconds() const {
        return static_cast<float>(AsMicroseconds()) / 1000000.0f;
    }

    std::size_t TimeSpan::AsMilliseconds() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();
    }

    std::size_t TimeSpan::AsMicroseconds() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(_end - _start).count();
    }

    Timer::Timer(): _started(false) {
        Start();
    }

    void Timer::Start() {
        if (!_started) {
            _started = true;
            _start = Clock::now();
        }
    }

    TimeSpan Timer::Restart() {
        const TimePoint tmp = Clock::now();
        if (_started)
            _end = tmp;
        _started = true;
        const TimeSpan span(_start, tmp);
        _start = tmp;
        return span;
    }

    TimeSpan Timer::Reset() {
        const TimePoint tmp = Clock::now();
        if (_started)
            _end = tmp;
        _started = false;
        return {_start, tmp};
    }

    TimeSpan Timer::GetElapsed() const {
        if (_started)
            return {_start, Clock::now()};
        return {_start, _end};
    }


    TimeSpan Timer::Stop() {
        if (_started) {
            _started = false;
            _end = Clock::now();
        }
        return {_start, _end};
    }
}
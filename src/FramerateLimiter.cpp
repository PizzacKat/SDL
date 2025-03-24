#include "SDL/FramerateLimiter.hpp"

#include <SDL3/SDL_timer.h>

namespace SDL {
    FramerateLimiter::FramerateLimiter(): _target(-1) {

    }

    FramerateLimiter::FramerateLimiter(const FramerateType target): _target(target) {

    }

    FramerateType FramerateLimiter::GetTarget() const {
        return _target;
    }

    FramerateType FramerateLimiter::SetTarget(const FramerateType target) {
        const FramerateType tmp = _target;
        _target = target;
        return tmp;
    }


    FramerateType FramerateLimiter::Update() {
        const TimeSpan time = _timer.Stop();
        const std::size_t ms = 1000000 / _target;
        if (time.AsMicroseconds() >= ms) {
            _timer.Start();
            return 1000000 / time.AsMicroseconds();
        }
        SDL_DelayPrecise((ms - time.AsMicroseconds()) * 1000);
        _timer.Start();
        return _target;
    }
}

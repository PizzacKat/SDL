#ifndef FRAMERATELIMITER_HPP
#define FRAMERATELIMITER_HPP

#include "Timer.hpp"

namespace SDL {
    typedef std::uint32_t FramerateType;
    class FramerateLimiter {
    public:
        FramerateLimiter();
        explicit FramerateLimiter(FramerateType target);

        [[nodiscard]] FramerateType GetTarget() const;
        FramerateType SetTarget(FramerateType target);

        FramerateType Update();
    private:
        Timer _timer;
        FramerateType _target;
    };
}

#endif //FRAMERATELIMITER_HPP

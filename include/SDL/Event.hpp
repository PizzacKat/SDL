#ifndef EVENT_HPP
#define EVENT_HPP

#include <optional>
#include <SDL3/SDL_events.h>

namespace SDL {
    typedef SDL_Event Event;

    inline std::optional<Event> PollEvent() {
        SDL_Event event;
        if (!SDL_PollEvent(&event))
            return std::nullopt;
        return event;
    }
}

#endif //EVENT_HPP

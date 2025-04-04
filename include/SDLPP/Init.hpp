#ifndef INIT_HPP
#define INIT_HPP
#include <stdexcept>
#include <string>
#include <SDL3/SDL_init.h>

namespace SDL::Init {
    extern SDL_InitFlags flags;

    class AutoInit {
    public:
        AutoInit() {
            if (!SDL_Init(flags))
                throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
        }

        AutoInit(const AutoInit &)= delete;
        AutoInit& operator=(const AutoInit &)= delete;
        AutoInit(AutoInit &&) noexcept= delete;
        AutoInit& operator=(AutoInit &&) noexcept= delete;

        ~AutoInit() {
            SDL_Quit();
        }
    };
}

#endif //INIT_HPP

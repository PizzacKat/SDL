#ifndef ERROR_HPP
#define ERROR_HPP

#include <functional>
#include <iostream>
#include <stdexcept>
#include <SDL3/SDL_error.h>

namespace SDL::Error {
    class Error : public std::runtime_error {
    public:
        explicit Error(const std::string &msg) : std::runtime_error(msg) {

        }

        explicit Error(const char* msg) : std::runtime_error(msg) {

        }
    };

    struct DefaultCallback {
        void operator()(const std::string &function, const char *error) const {
            char errstr[512];
            std::snprintf(errstr, 512, "%s (%s)", function.c_str(), error);
            throw Error(errstr);
        }
    };

    extern std::function<void(const std::string &, const char *)> callback;

    inline void Throw(const std::string &function) {
        callback(function, SDL_GetError());
    }
}

#endif //ERROR_HPP

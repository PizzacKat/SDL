#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <stdexcept>
#include <string>
#include <SDL3/SDL_video.h>

#include "Vector.hpp"

namespace SDL {
    class Window {
    public:
        Window(const std::string &title, const Vector2<> &size, SDL_WindowFlags flags = 0);

        Window(const Window &)= delete;
        Window &operator=(const Window &) = delete;
        Window(Window &&window) noexcept;

        Window &operator=(Window &&window) noexcept;

        [[nodiscard]] SDL_Window *Get() const;

        operator SDL_Window *() const;

        void SetTitle(const std::string &title);
        [[nodiscard]] std::string GetTitle() const;

        void SetSize(const Vector2<> &size);
        [[nodiscard]] Vector2<> GetSize() const;

        void SetPosition(const Vector2<> &position);
        [[nodiscard]] Vector2<> GetPosition() const;

        ~Window();
    private:
        SDL_Window *_window;
    };
}

#endif //WINDOW_HPP

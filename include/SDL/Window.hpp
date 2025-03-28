#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>
#include <SDL3/SDL_video.h>

#include "APIObject.hpp"
#include "Surface.hpp"
#include "Vector.hpp"

namespace SDL {
    class Window {
    public:
        Window(Window &&window) noexcept;

        Window &operator=(Window &&window) noexcept;
        Window(const std::string &title, const Vector2<> &size, SDL_WindowFlags flags = 0);

        Window(SDL_Window *window);
        Window(SDL_Window *window, Borrowed borrowed);

        [[nodiscard]] SDL_Window *Get() const;

        operator SDL_Window *() const;

        void SetTitle(const std::string &title);
        [[nodiscard]] std::string GetTitle() const;

        void SetSize(const Vector2<> &size);
        [[nodiscard]] Vector2<> GetSize() const;

        void SetPosition(const Vector2<> &position);
        [[nodiscard]] Vector2<> GetPosition() const;

        void SetShape(const Surface &shape);
    private:
        Object::APIObject<SDL_Window *> _window;
    };
}

#endif //WINDOW_HPP

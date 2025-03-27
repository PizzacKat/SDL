#include "SDL/Window.hpp"
#include "SDL/Error.hpp"

namespace SDL {
    Window::Window(const std::string &title, const Vector2<> &size, const SDL_WindowFlags flags): _window(SDL_CreateWindow(title.c_str(), size.x, size.y, flags)) {
        if (!_window)
            Error::Throw("SDL_CreateWindow");
    }

    Window::Window(Window &&window) noexcept: _window(window._window) {
        window._window = nullptr;
    }

    Window &Window::operator=(Window &&window) noexcept {
        if (_window)
            SDL_DestroyWindow(_window);
        _window = window._window;
        window._window = nullptr;
        return *this;
    }

    SDL_Window *Window::Get() const {
        return _window;
    }

    Window::operator SDL_Window *() const {
        return _window;
    }

    void Window::SetTitle(const std::string &title) {
        if (!SDL_SetWindowTitle(_window, title.c_str()))
            Error::Throw("SDL_SetWindowTitle");
    }

    std::string Window::GetTitle() const {
        return SDL_GetWindowTitle(_window);
    }

    void Window::SetSize(const Vector2<> &size) {
        if (!SDL_SetWindowSize(_window, size.x, size.y))
            Error::Throw("SDL_SetWindowSize");
    }

    Vector2<> Window::GetSize() const {
        Vector2<> size;
        if (!SDL_GetWindowSize(_window, &size.x, &size.y))
            Error::Throw("SDL_GetWindowSize");
        return size;
    }

    void Window::SetPosition(const Vector2<> &position) {
        if (!SDL_SetWindowPosition(_window, position.x, position.y))
            Error::Throw("SDL_SetWindowPosition");
    }

    Vector2<> Window::GetPosition() const {
        Vector2<> position;
        if (!SDL_GetWindowPosition(_window, &position.x, &position.y))
            Error::Throw("SDL_GetWindowPosition");
        return position;
    }

    Window::~Window() {
        if (_window)
            SDL_DestroyWindow(_window);
    }
}

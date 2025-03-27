#include "SDL/Renderer.hpp"
#include "SDL/Error.hpp"

namespace SDL {
    Renderer::Renderer(class Window &window): _window(&window), _renderer(SDL_CreateRenderer(window, nullptr)) {
        if (!_renderer)
            Error::Throw("SDL_CreateRenderer");
    }

    Renderer::Renderer(class Window &window, const std::string &name): _window(&window), _renderer(SDL_CreateRenderer(window, name.c_str())) {
        if (!_renderer)
            Error::Throw("SDL_CreateRenderer");
    }

    Renderer::Renderer(Renderer &&renderer) noexcept: _window(renderer._window), _renderer(renderer._renderer) {
        renderer._renderer = nullptr;
    }

    Renderer & Renderer::operator=(Renderer &&renderer) noexcept {
        if (_renderer)
            SDL_DestroyRenderer(_renderer);
        _window = renderer._window;
        _renderer = renderer._renderer;
        renderer._renderer = nullptr;
        return *this;
    }

    Window &Renderer::Window() const {
        return *_window;
    }

    Texture *Renderer::Target() const {
        return _target;
    }

    void Renderer::SetTarget(std::nullptr_t) {
        if (!SDL_SetRenderTarget(_renderer, nullptr))
            Error::Throw("SDL_SetRenderTarget");
        _target = nullptr;
    }

    void Renderer::SetTarget(Texture &texture) {
        if (!SDL_SetRenderTarget(_renderer, texture.Get()))
            Error::Throw("SDL_SetRenderTarget");
        _target = &texture;
    }

    SDL_Renderer *Renderer::Get() const {
        return _renderer;
    }

    Renderer::operator SDL_Renderer *() const {
        return _renderer;
    }

    void Renderer::SetDrawColor(const Color &color) {
        if (!SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a))
            Error::Throw("SDL_SetRenderDrawColor");
    }

    Color Renderer::GetDrawColor() const {
        Color color;
        if (!SDL_GetRenderDrawColor(_renderer, &color.r, &color.g, &color.b, &color.a))
            Error::Throw("SDL_GetRenderDrawColor");
        return color;
    }

    void Renderer::Clear() {
        if (!SDL_RenderClear(_renderer))
            Error::Throw("SDL_RenderClear");
    }

    void Renderer::Clear(const Color &color) {
        const Color tmp = GetDrawColor();
        SetDrawColor(color);
        if (!SDL_RenderClear(_renderer))
            Error::Throw("SDL_RenderClear");
        SetDrawColor(tmp);
    }

    void Renderer::Draw(const SDL_Vertex *vertices, const int vertexCount, const Texture &texture) {
        if (!SDL_RenderGeometry(_renderer, texture ? texture.Get() : nullptr, vertices, vertexCount, nullptr, 0))
            Error::Throw("SDL_RenderGeometry");
    }

    void Renderer::Draw(const SDL_Vertex *vertices, const int vertexCount, const int *indices, const int indexCount,
        const Texture &texture) {
        if (!SDL_RenderGeometry(_renderer, texture ? texture.Get() : nullptr, vertices, vertexCount, indices, indexCount))
            Error::Throw("SDL_RenderGeometry");
    }

    void Renderer::Draw(const VertexBuffer &vertices, const Texture &texture) {
        if (!SDL_RenderGeometry(_renderer, texture ? texture.Get() : nullptr, vertices.Vertices(), static_cast<int>(vertices.VertexCount()), vertices.Indices(), static_cast<int>(vertices.IndexCount())))
            Error::Throw("SDL_RenderGeometry");
    }

    void Renderer::Draw(const Drawable &drawable) {
        drawable.Draw(*this);
    }

    void Renderer::SetViewport(const std::optional<Rect<>> &rect) {
        if (rect) {
            const SDL_Rect vp = rect.value();
            if (!SDL_SetRenderViewport(_renderer, &vp))
                Error::Throw("SDL_SetRenderViewport");
        } else {
            if (!SDL_SetRenderViewport(_renderer, nullptr))
                Error::Throw("SDL_SetRenderViewport");
        }
    }

    Rect<> Renderer::GetViewport() const {
        SDL_Rect vp;
        if (!SDL_GetRenderViewport(_renderer, &vp))
            Error::Throw("SDL_GetRenderViewport");
        return vp;
    }

    void Renderer::SetClipRect(const std::optional<Rect<>> &rect) {
        if (rect) {
            const SDL_Rect cr = rect.value();
            if (!SDL_SetRenderClipRect(_renderer, &cr))
                Error::Throw("SDL_SetRenderClipRect");
        } else {
            if (!SDL_SetRenderClipRect(_renderer, nullptr))
                Error::Throw("SDL_SetRenderClipRect");
        }
    }

    Rect<> Renderer::GetClipRect() const {
        SDL_Rect cr;
        if (!SDL_GetRenderClipRect(_renderer, &cr))
            Error::Throw("SDL_GetRenderClipRect");
        return cr;
    }


    void Renderer::SetVSync(const bool enable) {
        if (!SDL_SetRenderVSync(_renderer, enable ? SDL_RENDERER_VSYNC_ADAPTIVE : SDL_RENDERER_VSYNC_DISABLED))
            Error::Throw("SDL_SetRenderVSync");
    }

    [[nodiscard]] bool Renderer::GetVSync() const {
        int vsync;
        if (!SDL_GetRenderVSync(_renderer, &vsync))
            Error::Throw("SDL_GetRenderVSync");
        return vsync == SDL_RENDERER_VSYNC_ADAPTIVE;
    }


    void Renderer::Display() {
        if (!SDL_RenderPresent(_renderer))
            Error::Throw("SDL_RenderPresent");
    }

    Renderer::~Renderer() {
        if (_renderer)
            SDL_DestroyRenderer(_renderer);
    }
}

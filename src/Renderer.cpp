#include "SDLPP/Renderer.hpp"
#include "SDLPP/Error.hpp"

namespace SDL {
    Renderer::Renderer(class Window &window): _renderer(SDL_CreateRenderer(window, nullptr)) {
        if (!_renderer)
            Error::Throw("SDL_CreateRenderer");
    }

    Renderer::Renderer(const Properties &properties): _renderer(SDL_CreateRendererWithProperties(properties)) {
        if (!_renderer)
            Error::Throw("SDL_CreateRendererWithProperties");
    }

    Renderer::Renderer(Renderer &&renderer) noexcept: _renderer(std::move(renderer._renderer)) {

    }

    Renderer &Renderer::operator=(Renderer &&renderer) noexcept {
        _renderer = std::move(renderer._renderer);
        return *this;
    }

    Renderer::Renderer(const class Window &window, const std::string &name): _renderer(SDL_CreateRenderer(window, name.c_str())) {
        if (!_renderer)
            Error::Throw("SDL_CreateRenderer");
    }

    Renderer::Renderer(SDL_Renderer *renderer): _renderer(renderer) {

    }

    Renderer::Renderer(SDL_Renderer *renderer, const Borrowed borrowed): _renderer(renderer, borrowed) {

    }

    Window Renderer::GetWindow() const {
        return {SDL_GetRenderWindow(_renderer), Borrowed()};
    }

    Texture Renderer::Target() const {
        return {SDL_GetRenderTarget(_renderer), Borrowed()};
    }

    void Renderer::SetTarget(std::nullptr_t) {
        if (!SDL_SetRenderTarget(_renderer, nullptr))
            Error::Throw("SDL_SetRenderTarget");
    }

    void Renderer::SetTarget(Texture &texture) {
        if (!SDL_SetRenderTarget(_renderer, texture.Get()))
            Error::Throw("SDL_SetRenderTarget");
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

    Properties Renderer::GetProperties() const {
        const SDL_PropertiesID id = SDL_GetRendererProperties(_renderer);
        if (id == 0)
            Error::Throw("SDL_GetRendererProperties");
        return {id, Borrowed()};
    }
}

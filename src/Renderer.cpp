#include "SDL/Renderer.hpp"

namespace SDL {
    Renderer::Renderer(class Window &window): _window(&window), _renderer(SDL_CreateRenderer(window, nullptr)) {
        if (!_renderer)
            throw std::runtime_error("Failed to create renderer");
    }

    Renderer::Renderer(class Window &window, const std::string &name): _window(&window), _renderer(SDL_CreateRenderer(window, name.c_str())) {
        if (!_renderer)
            throw std::runtime_error("Failed to create renderer");
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
        SDL_SetRenderTarget(_renderer, nullptr);
        _target = nullptr;
    }

    void Renderer::SetTarget(Texture &texture) {
        SDL_SetRenderTarget(_renderer, texture.Get());
        _target = &texture;
    }

    SDL_Renderer *Renderer::Get() const {
        return _renderer;
    }

    Renderer::operator SDL_Renderer *() const {
        return _renderer;
    }

    void Renderer::SetDrawColor(const Color &color) {
        SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    }

    Color Renderer::GetDrawColor() const {
        Color color;
        SDL_GetRenderDrawColor(_renderer, &color.r, &color.g, &color.b, &color.a);
        return color;
    }

    void Renderer::Clear() {
        SDL_RenderClear(_renderer);
    }

    void Renderer::Clear(const Color &color) {
        const Color tmp = GetDrawColor();
        SetDrawColor(color);
        SDL_RenderClear(_renderer);
        SetDrawColor(tmp);
    }

    void Renderer::Draw(const SDL_Vertex *vertices, const int vertexCount, const Texture &texture) {
        SDL_RenderGeometry(_renderer, texture ? texture.Get() : nullptr, vertices, vertexCount, nullptr, 0);
    }

    void Renderer::Draw(const SDL_Vertex *vertices, const int vertexCount, const int *indices, const int indexCount,
        const Texture &texture) {
        SDL_RenderGeometry(_renderer, texture ? texture.Get() : nullptr, vertices, vertexCount, indices, indexCount);
    }

    void Renderer::Draw(const VertexBuffer &vertices, const Texture &texture) {
        SDL_RenderGeometry(_renderer, texture ? texture.Get() : nullptr, vertices.Vertices(), static_cast<int>(vertices.VertexCount()), vertices.Indices(), static_cast<int>(vertices.IndexCount()));
    }

    void Renderer::Draw(const Drawable &drawable) {
        drawable.Draw(*this);
    }

    void Renderer::SetViewport(const std::optional<Rect<>> &rect) {
        if (rect) {
            const SDL_Rect vp = rect.value();
            SDL_SetRenderViewport(_renderer, &vp);
        } else {
            SDL_SetRenderViewport(_renderer, nullptr);
        }
    }

    Rect<> Renderer::GetViewport() const {
        SDL_Rect vp;
        SDL_GetRenderViewport(_renderer, &vp);
        return vp;
    }

    void Renderer::SetVSync(const bool enable) {
        SDL_SetRenderVSync(_renderer, enable ? SDL_RENDERER_VSYNC_ADAPTIVE : SDL_RENDERER_VSYNC_DISABLED);
    }

    [[nodiscard]] bool Renderer::GetVSync() const {
        int vsync;
        SDL_GetRenderVSync(_renderer, &vsync);
        return vsync == SDL_RENDERER_VSYNC_ADAPTIVE;
    }


    void Renderer::Display() {
        SDL_RenderPresent(_renderer);
    }

    Renderer::~Renderer() {
        if (_renderer)
            SDL_DestroyRenderer(_renderer);
    }
}

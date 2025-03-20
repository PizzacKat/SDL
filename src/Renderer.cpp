#include "SDL/Renderer.hpp"
#include <SDL3_image/SDL_image.h>

namespace SDL {
    Texture::Texture() = default;

    Texture::Texture(const std::nullptr_t) {

    }

    Texture::Texture(SDL_Texture *texture): _texture(texture, &SDL_DestroyTexture) {

    }

    void Texture::LoadFile(const Renderer &renderer, const std::string &file) {
        _texture = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderer, file.c_str()), SDL_DestroyTexture);
    }

    FVector2 Texture::GetSize() const {
        if (_texture == nullptr)
            return {0, 0};
        FVector2 size;
        SDL_GetTextureSize(_texture.get(), &size.x, &size.y);
        return size;
    }

    SDL_Texture *Texture::Get() const {
        return _texture.get();
    }

    Texture::operator bool() const {
        return _texture != nullptr;
    }

    bool Texture::operator==(const std::nullptr_t) const {
        return _texture == nullptr;
    }

    Texture::operator SDL_Texture*() const {
        return _texture.get();
    }

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

    void Renderer::Display() {
        SDL_RenderPresent(_renderer);
    }

    Renderer::~Renderer() {
        if (_renderer)
            SDL_DestroyRenderer(_renderer);
    }
}

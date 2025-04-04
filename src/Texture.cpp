#include "SDLPP/Texture.hpp"

#include "SDLPP/Error.hpp"
#include "SDLPP/Renderer.hpp"
#include "SDL3_image/SDL_image.h"

namespace SDL {
    Texture::Texture() = default;

    Texture::Texture(Texture &&texture) noexcept: _texture(std::move(texture._texture)) {
    }

    Texture &Texture::operator=(Texture &&texture) noexcept {
        _texture = std::move(texture._texture);
        return *this;
    }

    Texture::Texture(SDL_Texture *texture): _texture(texture) {

    }

    Texture::Texture(SDL_Texture *texture, const Borrowed borrowed): _texture(texture, borrowed) {

    }

    void Texture::Create(const Renderer &renderer, const UVector2 &size, const SDL_PixelFormat format, const SDL_TextureAccess access) {
        if (_texture != nullptr)
            SDL_DestroyTexture(_texture);
        _texture = SDL_CreateTexture(renderer, format, access, static_cast<int>(size.x), static_cast<int>(size.y));
        if (_texture == nullptr)
            Error::Throw("SDL_CreateTexture");
    }

    void Texture::LoadFile(const Renderer &renderer, const std::string &file) {
        if (_texture != nullptr)
            SDL_DestroyTexture(_texture);
        _texture = IMG_LoadTexture(renderer, file.c_str());
    }

    FVector2 Texture::GetSize() const {
        if (_texture == nullptr)
            return {0, 0};
        FVector2 size;
        if (!SDL_GetTextureSize(_texture, &size.x, &size.y))
            Error::Throw("SDL_GetTextureSize");
        return size;
    }

    SDL_Texture *Texture::Get() const {
        return _texture;
    }

    void Texture::Update(const Rect<> rect, const void *pixels, const int pitch) {
        const SDL_Rect sdl_rect = rect;
        if (!SDL_UpdateTexture(_texture, &sdl_rect, pixels, pitch))
            Error::Throw("SDL_UpdateTexture");
    }

    void Texture::Lock(const Rect<> rect, void **pixels, int &pitch) {
        const SDL_Rect sdl_rect = rect;
        if (!SDL_LockTexture(_texture, &sdl_rect, pixels, &pitch))
            Error::Throw("SDL_LockTexture");
    }

    void Texture::Unlock() {
        SDL_UnlockTexture(_texture);
    }

    Texture::operator bool() const {
        return _texture != nullptr;
    }

    bool Texture::operator==(const std::nullptr_t) const {
        return _texture == nullptr;
    }

    Texture::operator SDL_Texture*() const {
        return _texture;
    }
}
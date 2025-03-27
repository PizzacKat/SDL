#include "SDL/Texture.hpp"
#include "SDL/Renderer.hpp"
#include "SDL3_image/SDL_image.h"

namespace SDL {
    Texture::Texture() = default;

    Texture::Texture(const std::nullptr_t) {

    }

    Texture::Texture(SDL_Texture *texture): _texture(texture) {

    }

    void Texture::Create(const Renderer &renderer, const UVector2 &size, const SDL_PixelFormat format, const SDL_TextureAccess access) {
        if (_texture != nullptr)
            SDL_DestroyTexture(_texture);
        _texture = SDL_CreateTexture(renderer, format, access, static_cast<int>(size.x), static_cast<int>(size.y));
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
        SDL_GetTextureSize(_texture, &size.x, &size.y);
        return size;
    }

    SDL_Texture *Texture::Get() const {
        return _texture;
    }

    void Texture::Update(const Rect<> rect, const void *pixels, const int pitch) {
        const SDL_Rect sdl_rect = rect;
        SDL_UpdateTexture(_texture, &sdl_rect, pixels, pitch);
    }

    void Texture::Lock(const Rect<> rect, void **pixels, int &pitch) {
        const SDL_Rect sdl_rect = rect;
        SDL_LockTexture(_texture, &sdl_rect, pixels, &pitch);
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

    Texture::~Texture() {
        if (_texture != nullptr)
            SDL_DestroyTexture(_texture);
    }
}
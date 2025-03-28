#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <cstddef>
#include <memory>
#include <string>
#include <SDL3/SDL_render.h>

#include "APIObject.hpp"
#include "Rect.hpp"
#include "Vector.hpp"

namespace SDL {
    class Renderer;

    class Texture {
    public:
        Texture();
        Texture(Texture &&texture) noexcept;
        Texture &operator=(Texture &&texture) noexcept;

        Texture(SDL_Texture *texture);
        Texture(SDL_Texture *texture, Borrowed borrowed);

        void Create(const Renderer &renderer, const UVector2 &size, SDL_PixelFormat format = SDL_PIXELFORMAT_RGBA8888, SDL_TextureAccess access = SDL_TEXTUREACCESS_STATIC);
        void LoadFile(const Renderer &renderer, const std::string &file);

        [[nodiscard]] FVector2 GetSize() const;
        [[nodiscard]] SDL_Texture *Get() const;

        void Update(Rect<> rect, const void *pixels, int pitch);
        void Lock(Rect<> rect, void **pixels, int &pitch);
        void Unlock();

        explicit operator bool() const;
        bool operator==(std::nullptr_t) const;

        operator SDL_Texture *() const;
    private:
        Object::APIObject<SDL_Texture *> _texture = nullptr;
    };
}

#endif //TEXTURE_HPP

#ifndef SURFACE_HPP
#define SURFACE_HPP
#include <SDL3/SDL_surface.h>

#include "APIObject.hpp"
#include "Color.hpp"
#include "Error.hpp"
#include "Rect.hpp"
#include "Vector.hpp"


namespace SDL {
    class Surface {
    public:
        Surface();
        Surface(Surface &&surface) noexcept;
        Surface &operator=(Surface &&surface) noexcept;

        Surface(Vector2<> size, SDL_PixelFormat format);
        Surface(Vector2<> size, SDL_PixelFormat format, void *data, int pitch);

        Surface(SDL_Surface *surface);
        Surface(SDL_Surface *surface, Borrowed borrowed);

        void Clear(const Color &color);

        void Blit(const std::optional<Rect<>> &srcRect, Surface &dst, const std::optional<Rect<>> &dstRect);
        void Blit9Grid(const std::optional<Rect<>> &srcRect, int leftWidth, int rightWidth, int topHeight, int bottomHeight, float scale, SDL_ScaleMode scaleMode, Surface &dst, const std::optional<Rect<>> &dstRect);
        void BlitScaled(const std::optional<Rect<>> &srcRect, Surface &dst, const std::optional<Rect<>> &dstRect, SDL_ScaleMode scaleMode);
        void BlitTiled(const std::optional<Rect<>> &srcRect, Surface &dst, const std::optional<Rect<>> &dstRect);
        void BlitUnchecked(Rect<> srcRect, Surface &dst, Rect<> dstRect);
        void BlitUncheckedScaled(Rect<> srcRect, Surface &dst, Rect<> dstRect, SDL_ScaleMode scaleMode);
        void BlitTiledWithScale(const std::optional<Rect<>> &srcRect, float scale, SDL_ScaleMode scaleMode, Surface &dst, const std::optional<Rect<>> &dstRect);

        void AddAlternateImage(Surface &image);

        [[nodiscard]] Vector2<> GetSize() const;

        Surface Convert(SDL_PixelFormat format);
        Surface Duplicate();

        std::vector<Surface> GetImages() const;

        void FillRect(Rect<> rect, Uint32 color);
        void FillRects(const Rect<> rects[], std::size_t rectCount, Uint32 color);

        template<typename Container>
        void FillRects(const Container &rects, const Uint32 color) {
            FillRects(rects.data(), rects.size(), color);
        }

        template<typename ... Args>
        std::enable_if_t<std::conjunction_v<std::is_same<Args, Rect<>>...>> FillRects(const Uint32 color, const Args &...rects) {
            SDL_Rect sdl_rects[sizeof...(rects)] = {rects...};
            FillRects(sdl_rects, sizeof...(rects), color);
        }

        void Flip(SDL_FlipMode flipMode);

        void SetAlphaMod(Uint8 alphaMod);
        [[nodiscard]] Uint8 GetAlphaMod() const;

        void SetBlendMode(SDL_BlendMode blendMode);
        [[nodiscard]] SDL_BlendMode GetBlendMode() const;

        void SetClipRect(Rect<> rect);
        [[nodiscard]] Rect<> GetClipRect() const;

        void SetColorKey(bool enabled, Uint32 colorKey);
        [[nodiscard]] Uint32 GetColorKey() const;
        [[nodiscard]] bool HasColorKey() const;

        void SetColorMod(Color color);
        [[nodiscard]] Color GetColorMod() const;

        void SetColorspace(SDL_Colorspace colorspace);
        [[nodiscard]] SDL_Colorspace GetColorspace() const;

        void SetRLE(bool enabled);
        [[nodiscard]] bool GetRLE() const;

        [[nodiscard]] SDL_PropertiesID GetProperties() const;

        void Lock();
        void Unlock();

        [[nodiscard]] Uint32 MapRGB(Color color) const;
        [[nodiscard]] Uint32 MapRGBA(Color color) const;

        void PremultiplyAlpha(bool linear);

        void Stretch(Rect<> srcRect, Surface &dst, Rect<> dstRect, SDL_ScaleMode scaleMode);

        void WritePixel(Vector2<> position, Color color);
        void WritePixelFloat(Vector2<> position, FColor color);

        [[nodiscard]] SDL_Surface *Get() const;
        operator SDL_Surface *() const;

        ~Surface();
    private:
        Object::APIObject<SDL_Surface *> _surface = nullptr;
    };
}

#endif //SURFACE_HPP

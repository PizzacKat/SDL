#include "SDLPP/Surface.hpp"

namespace SDL {
    Surface::Surface() = default;

    Surface::Surface(SDL_Surface *surface): _surface(surface) {

    }

    Surface::Surface(SDL_Surface *surface, const Borrowed borrowed): _surface(surface, borrowed) {

    }

    Surface::Surface(const Vector2<> size, const SDL_PixelFormat format): _surface(SDL_CreateSurface(size.x, size.y, format)) {
        if (_surface == nullptr)
            Error::Throw("SDL_CreateSurface");
    }

    Surface::Surface(const Vector2<> size, const SDL_PixelFormat format, void *data, const int pitch): _surface(SDL_CreateSurfaceFrom(size.x, size.y, format, data, pitch)) {

    }

    Surface::Surface(Surface &&surface) noexcept: _surface(std::move(surface._surface)) {

    }

    Surface &Surface::operator=(Surface &&surface) noexcept {
        _surface = std::move(surface._surface);
        return *this;
    }

    void Surface::Clear(const Color &color) {
        if (!SDL_ClearSurface(_surface, color.r, color.g, color.b, color.a))
            Error::Throw("SDL_ClearSurface");
    }

    void Surface::Blit(const std::optional<Rect<>> &srcRect, Surface &dst, const std::optional<Rect<>> &dstRect) {
        const SDL_Rect sdl_src = srcRect.value_or(SDL_Rect()), sdl_dst = dstRect.value_or(SDL_Rect());
        if (!SDL_BlitSurface(_surface, srcRect ? &sdl_src : nullptr, dst, dstRect ? &sdl_dst : nullptr))
            Error::Throw("SDL_BlitSurface");

    }

    void Surface::Blit9Grid(const std::optional<Rect<>> &srcRect, const int leftWidth, const int rightWidth,
        const int topHeight, const int bottomHeight, const float scale, const SDL_ScaleMode scaleMode, Surface &dst,
        const std::optional<Rect<>> &dstRect) {
        const SDL_Rect sdl_src = srcRect.value_or(SDL_Rect()), sdl_dst = dstRect.value_or(SDL_Rect());
        if (!SDL_BlitSurface9Grid(_surface, srcRect ? &sdl_src : nullptr, leftWidth, rightWidth, topHeight, bottomHeight, scale, scaleMode, dst, dstRect ? &sdl_dst : nullptr))
            Error::Throw("SDL_BlitSurface9Grid");

    }

    void Surface::BlitScaled(const std::optional<Rect<>> &srcRect, Surface &dst, const std::optional<Rect<>> &dstRect,
        const SDL_ScaleMode scaleMode) {
        const SDL_Rect sdl_src = srcRect.value_or(SDL_Rect()), sdl_dst = dstRect.value_or(SDL_Rect());
        if (!SDL_BlitSurfaceScaled(_surface, srcRect ? &sdl_src : nullptr, dst, dstRect ? &sdl_dst : nullptr, scaleMode))
            Error::Throw("SDL_BlitSurfaceScaled");
    }

    void Surface::BlitTiled(const std::optional<Rect<>> &srcRect, Surface &dst, const std::optional<Rect<>> &dstRect) {
        const SDL_Rect sdl_src = srcRect.value_or(SDL_Rect()), sdl_dst = dstRect.value_or(SDL_Rect());
        if (!SDL_BlitSurfaceTiled(_surface, srcRect ? &sdl_src : nullptr, dst, dstRect ? &sdl_dst : nullptr))
            Error::Throw("SDL_BlitSurfaceTiled");
    }

    void Surface::BlitUnchecked(const Rect<> srcRect, Surface &dst, const Rect<> dstRect) {
        const SDL_Rect sdl_src = srcRect, sdl_dst = dstRect;
        if (!SDL_BlitSurfaceUnchecked(_surface, &sdl_src, dst, &sdl_dst))
            Error::Throw("SDL_BlitSurfaceUnchecked");
    }

    void Surface::BlitUncheckedScaled(const Rect<> srcRect, Surface &dst, const Rect<> dstRect,
        const SDL_ScaleMode scaleMode) {
        const SDL_Rect sdl_src = srcRect, sdl_dst = dstRect;
        if (!SDL_BlitSurfaceUncheckedScaled(_surface, &sdl_src, dst, &sdl_dst, scaleMode))
            Error::Throw("SDL_BlitSurfaceUncheckedScaled");
    }

    void Surface::BlitTiledWithScale(const std::optional<Rect<>> &srcRect, const float scale,
        const SDL_ScaleMode scaleMode, Surface &dst, const std::optional<Rect<>> &dstRect) {
        const SDL_Rect sdl_src = srcRect.value_or(SDL_Rect()), sdl_dst = dstRect.value_or(SDL_Rect());
        if (!SDL_BlitSurfaceTiledWithScale(_surface, srcRect ? &sdl_src : nullptr, scale, scaleMode, dst, dstRect ? &sdl_dst : nullptr))
            Error::Throw("SDL_BlitSurfaceTiledWithScale");
    }

    void Surface::AddAlternateImage(Surface &image) {
        if (!SDL_AddSurfaceAlternateImage(_surface, image))
            Error::Throw("SDL_AddSurfaceAlternateImage");
    }

    Vector2<> Surface::GetSize() const {
        if (_surface == nullptr) {
            Error::Throw("SDL_Surface", "Pointer is null");
            return {};
        }
        return {_surface->w, _surface->h};
    }

    Surface Surface::Convert(const SDL_PixelFormat format) {
        SDL_Surface *surface = SDL_ConvertSurface(_surface, format);
        if (surface == nullptr)
            Error::Throw("SDL_ConvertSurface");
        return surface;
    }

    Surface Surface::Duplicate() {
        SDL_Surface *surface = SDL_DuplicateSurface(_surface);
        if (surface == nullptr)
            Error::Throw("SDL_DuplicateSurface");
        return surface;
    }

    std::vector<Surface> Surface::GetImages() const {
        int images;
        Object::APIObject surfaces = SDL_GetSurfaceImages(_surface, &images);
        if (surfaces == nullptr)
            Error::Throw("SDL_GetSurfaceImages");
        std::vector<Surface> result(images);
        for (int i = 0; i < images; ++i)
            result[i] = {surfaces[i], Borrowed()};
        return result;
    }

    void Surface::FillRect(const Rect<> rect, const Uint32 color) {
        const SDL_Rect sdl_rect = rect;
        if (!SDL_FillSurfaceRect(_surface, &sdl_rect, color))
            Error::Throw("SDL_FillSurfaceRect");
    }

    void Surface::FillRects(const Rect<> rects[], const std::size_t rectCount, const Uint32 color) {
        std::vector<SDL_Rect> sdl_rects(rectCount);
        std::transform(rects, rects + rectCount, sdl_rects.begin(), [](const SDL_Rect &rect) {
            return SDL_Rect(rect);
        });
        if (!SDL_FillSurfaceRects(_surface, sdl_rects.data(), static_cast<int>(rectCount), color))
            Error::Throw("SDL_FillSurfaceRects");
    }

    void Surface::Flip(const SDL_FlipMode flipMode) {
        if (!SDL_FlipSurface(_surface, flipMode))
            Error::Throw("SDL_FlipSurface");
    }

    void Surface::SetAlphaMod(const Uint8 alphaMod) {
        if (!SDL_SetSurfaceAlphaMod(_surface, alphaMod))
            Error::Throw("SDL_SetSurfaceAlphaMod");
    }

    Uint8 Surface::GetAlphaMod() const {
        Uint8 alphaMod = 0;
        if (!SDL_GetSurfaceAlphaMod(_surface, &alphaMod))
            Error::Throw("SDL_GetSurfaceAlphaMod");
        return alphaMod;
    }

    void Surface::SetBlendMode(const SDL_BlendMode blendMode) {
        if (!SDL_SetSurfaceBlendMode(_surface, blendMode))
            Error::Throw("SDL_SetSurfaceBlendMode");
    }

    SDL_BlendMode Surface::GetBlendMode() const {
        SDL_BlendMode blendMode = SDL_BLENDMODE_NONE;
        if (!SDL_GetSurfaceBlendMode(_surface, &blendMode))
            Error::Throw("SDL_GetSurfaceBlendMode");
        return blendMode;
    }

    void Surface::SetClipRect(const Rect<> rect) {
        SDL_Rect sdl_rect = rect;
        if (!SDL_SetSurfaceClipRect(_surface, &sdl_rect))
            Error::Throw("SDL_SetSurfaceClipRect");
    }

    Rect<> Surface::GetClipRect() const {
        SDL_Rect sdl_rect;
        if (!SDL_GetSurfaceClipRect(_surface, &sdl_rect))
            Error::Throw("SDL_GetSurfaceClipRect");
        return sdl_rect;
    }

    void Surface::SetColorKey(const bool enabled, const Uint32 colorKey) {
        if (!SDL_SetSurfaceColorKey(_surface, enabled, colorKey))
            Error::Throw("SDL_SetSurfaceColorKey");
    }

    Uint32 Surface::GetColorKey() const {
        Uint32 colorKey = 0;
        if (!SDL_GetSurfaceColorKey(_surface, &colorKey))
            Error::Throw("SDL_GetSurfaceColorKey");
        return colorKey;
    }

    void Surface::SetColorMod(const Color color) {
        if (!SDL_SetSurfaceColorMod(_surface, color.r, color.g, color.b))
            Error::Throw("SDL_SetSurfaceColorMod");
    }

    Color Surface::GetColorMod() const {
        Color colorMod{0, 0, 0};
        if (!SDL_GetSurfaceColorMod(_surface, &colorMod.r, &colorMod.g, &colorMod.b))
            Error::Throw("SDL_GetSurfaceColorMod");
        return colorMod;
    }

    void Surface::SetColorspace(const SDL_Colorspace colorspace) {
        if (!SDL_SetSurfaceColorspace(_surface, colorspace))
            Error::Throw("SDL_SetSurfaceColorspace");
    }

    SDL_Colorspace Surface::GetColorspace() const {
        return SDL_GetSurfaceColorspace(_surface);
    }

    void Surface::SetRLE(const bool enabled) {
        if (!SDL_SetSurfaceRLE(_surface, enabled))
            Error::Throw("SDL_SetSurfaceRLE");
    }

    bool Surface::GetRLE() const {
        return SDL_SurfaceHasRLE(_surface);
    }

    SDL_PropertiesID Surface::GetProperties() const {
        return SDL_GetSurfaceProperties(_surface);
    }

    void Surface::Lock() {
        if (!SDL_LockSurface(_surface))
            Error::Throw("SDL_LockSurface");
    }

    void Surface::Unlock() {
        SDL_UnlockSurface(_surface);
    }

    Uint32 Surface::MapRGB(const Color color) const {
        return SDL_MapSurfaceRGB(_surface, color.r, color.g, color.b);
    }

    Uint32 Surface::MapRGBA(const Color color) const {
        return SDL_MapSurfaceRGBA(_surface, color.r, color.g, color.b, color.a);
    }

    void Surface::PremultiplyAlpha(const bool linear) {
        if (!SDL_PremultiplySurfaceAlpha(_surface, linear))
            Error::Throw("SDL_PremultiplySurfaceAlpha");
    }

    void Surface::Stretch(const Rect<> srcRect, Surface &dst, const Rect<> dstRect, const SDL_ScaleMode scaleMode) {
        const SDL_Rect sdl_src = srcRect, dst_src = dstRect;
        if (!SDL_StretchSurface(_surface, &sdl_src, dst, &dst_src, scaleMode))
            Error::Throw("SDL_StretchSurface");
    }

    bool Surface::HasColorKey() const {
        return SDL_SurfaceHasColorKey(_surface);
    }

    void Surface::WritePixel(const Vector2<> position, const Color color) {
        if (!SDL_WriteSurfacePixel(_surface, position.x, position.y, color.r, color.g, color.b, color.a))
            Error::Throw("SDL_WriteSurfacePixel");
    }

    void Surface::WritePixelFloat(const Vector2<> position, const FColor color) {
        if (!SDL_WriteSurfacePixelFloat(_surface, position.x, position.y, color.r, color.g, color.b, color.a))
            Error::Throw("SDL_WriteSurfacePixelFloat");
    }

    SDL_Surface * Surface::Get() const {
        return _surface;
    }

    Surface::operator SDL_Surface*() const {
        return _surface;
    }

    Surface::~Surface() {
        if (_surface != nullptr)
            SDL_DestroySurface(_surface);
    }
}

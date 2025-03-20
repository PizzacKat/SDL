#ifndef COLOR_HPP
#define COLOR_HPP
#include <bits/stl_algo.h>
#include <SDL3/SDL_pixels.h>

namespace SDL {
    struct Color {
        Color();
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        Color(const SDL_Color &color);

        [[nodiscard]] Color AddColorClamped(const Color &other) const;
        [[nodiscard]] Color SubColorClamped(const Color &other) const;

        Color operator+(const Color &other) const;
        Color operator-(const Color &other) const;
        Color &operator+=(const Color &other);
        Color &operator-=(const Color &other);

        operator SDL_Color() const;

        unsigned char r, g, b, a;

        static Color Black;
        static Color White;
        static Color Red;
        static Color Yellow;
        static Color Green;
        static Color Cyan;
        static Color Blue;
        static Color Transparent;
    };

    struct FColor {
        FColor();
        FColor(float r, float g, float b, float a = 1.0f);
        FColor(SDL_FColor color);
        FColor(const Color &color);

        [[nodiscard]] FColor AddColorClamped(const FColor &other) const;
        [[nodiscard]] FColor SubColorClamped(const FColor &other) const;

        FColor operator+(const FColor &other) const;
        FColor operator-(const FColor &other) const;
        FColor &operator+=(const FColor &other);
        FColor &operator-=(const FColor &other);

        operator SDL_FColor() const;

        operator Color() const;

        float r, g, b, a;
    };
}

#endif //COLOR_HPP

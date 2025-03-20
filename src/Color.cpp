#include "SDL/Color.hpp"

namespace SDL {
    Color::Color(): r(0), g(0), b(0), a(255) {

    }

    Color::Color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a): r(r), g(g), b(b), a(a) {

    }

    Color::Color(const SDL_Color &color): r(color.r), g(color.g), b(color.b), a(color.a) {

    }

    Color Color::AddColorClamped(const Color &other) const {
        const int r = this->r + other.r;
        const int g = this->g + other.g;
        const int b = this->b + other.b;
        const int a = this->a + other.a;
        return {
            static_cast<unsigned char>(std::clamp(r, 0, 255)),
            static_cast<unsigned char>(std::clamp(g, 0, 255)),
            static_cast<unsigned char>(std::clamp(b, 0, 255)),
            static_cast<unsigned char>(std::clamp(a, 0, 255))
        };
    }

    Color Color::SubColorClamped(const Color &other) const {
        const int r = this->r - other.r;
        const int g = this->g - other.g;
        const int b = this->b - other.b;
        const int a = this->a - other.a;
        return {
            static_cast<unsigned char>(std::clamp(r, 0, 255)),
            static_cast<unsigned char>(std::clamp(g, 0, 255)),
            static_cast<unsigned char>(std::clamp(b, 0, 255)),
            static_cast<unsigned char>(std::clamp(a, 0, 255))
        };
    }

    Color Color::operator+(const Color &other) const {
        return AddColorClamped(other);
    }

    Color Color::operator-(const Color &other) const {
        return SubColorClamped(other);
    }

    Color & Color::operator+=(const Color &other) {
        return *this = *this + other;
    }

    Color & Color::operator-=(const Color &other) {
        return *this = *this - other;
    }

    Color::operator SDL_Color() const {
        return {r, g, b, a};
    }

    FColor::FColor(): r(0), g(0), b(0), a(1) {

    }

    FColor::FColor(const float r, const float g, const float b, const float a): r(r), g(g), b(b), a(a) {

    }

    FColor::FColor(const SDL_FColor color): r(color.r), g(color.g), b(color.b), a(color.a) {

    }

    FColor::FColor(const Color &color): r(static_cast<float>(color.r) / 255.0f), g(static_cast<float>(color.g) / 255.0f), b(static_cast<float>(color.b) / 255.0f), a(color.a) {

    }

    FColor FColor::AddColorClamped(const FColor &other) const {
        const float r = this->r + other.r;
        const float g = this->g + other.g;
        const float b = this->b + other.b;
        const float a = this->a + other.a;
        return {
            std::clamp(r, 0.0f, 255.0f),
            std::clamp(g, 0.0f, 255.0f),
            std::clamp(b, 0.0f, 255.0f),
            std::clamp(a, 0.0f, 255.0f)
        };
    }

    FColor FColor::SubColorClamped(const FColor &other) const {
        const float r = this->r - other.r;
        const float g = this->g - other.g;
        const float b = this->b - other.b;
        const float a = this->a - other.a;
        return {
            std::clamp(r, 0.0f, 255.0f),
            std::clamp(g, 0.0f, 255.0f),
            std::clamp(b, 0.0f, 255.0f),
            std::clamp(a, 0.0f, 255.0f)
        };
    }

    FColor FColor::operator+(const FColor &other) const {
        return AddColorClamped(other);
    }

    FColor FColor::operator-(const FColor &other) const {
        return SubColorClamped(other);
    }

    FColor & FColor::operator+=(const FColor &other) {
        return *this = *this + other;
    }

    FColor & FColor::operator-=(const FColor &other) {
        return *this = *this - other;
    }

    FColor::operator SDL_FColor() const {
        return {r, g, b, a};
    }

    FColor::operator Color() const {
        return {
            static_cast<Uint8>(r * 255),
            static_cast<Uint8>(g * 255),
            static_cast<Uint8>(b * 255),
            static_cast<Uint8>(a * 255)
        };
    }

    Color Color::Black(0, 0, 0);
    Color Color::White(255, 255, 255);
    Color Color::Red(255, 0, 0);
    Color Color::Yellow(255, 255, 0);
    Color Color::Green(0, 255, 0);
    Color Color::Cyan(0, 255, 255);
    Color Color::Blue(0, 0, 255);
    Color Color::Transparent(0, 0, 0, 0);
}

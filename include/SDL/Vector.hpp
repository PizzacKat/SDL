#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <cmath>
#include <type_traits>
#include <SDL3/SDL_rect.h>

namespace SDL {
    template <typename T = int>
    struct Vector2 {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "T must be a number type");

        constexpr Vector2(): x(0), y(0) {

        }

        constexpr Vector2(T x, T y): x(x), y(y) {

        }

        template <typename N>
        constexpr Vector2(const Vector2<N> &other): x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {

        }

        constexpr Vector2(SDL_Point point): x(static_cast<T>(point.x)), y(static_cast<T>(point.y)) {

        }

        constexpr Vector2(SDL_FPoint point): x(static_cast<T>(point.x)), y(static_cast<T>(point.y)) {

        }

        constexpr operator SDL_Point() const {
            return SDL_Point(static_cast<int>(x), static_cast<int>(y));
        }

        constexpr operator SDL_FPoint() const {
            return SDL_FPoint(static_cast<float>(x), static_cast<float>(y));
        }

        constexpr Vector2 operator+(const Vector2 &other) const {
            return Vector2(x + other.x, y + other.y);
        }

        constexpr Vector2 operator-(const Vector2 &other) const {
            return Vector2(x - other.x, y - other.y);
        }

        constexpr Vector2 operator*(const Vector2 &other) const {
            return Vector2(x * other.x, y * other.y);
        }

        constexpr Vector2 operator*(T other) const {
            return Vector2(x * other, y * other);
        }

        constexpr Vector2 operator/(T other) const {
            return Vector2(x / other, y / other);
        }

        constexpr Vector2 &operator+=(const Vector2 &other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        constexpr Vector2 &operator-=(const Vector2 &other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        constexpr Vector2 &operator*=(const Vector2 &other) {
            x *= other.x;
            y *= other.y;
            return *this;
        }

        constexpr Vector2 &operator*=(const T other) {
            x *= other;
            y *= other;
            return *this;
        }

        constexpr Vector2 &operator/=(const T other) {
            x /= other;
            y /= other;
            return *this;
        }

        [[nodiscard]] constexpr T Length() const {
            return std::sqrt(x * x + y * y);
        }

        [[nodiscard]] constexpr T LengthSq() const {
            return x * x + y * y;
        }

        [[nodiscard]] constexpr Vector2 Normalized() const {
            return Vector2(x / Length(),  y / Length());
        }

        constexpr bool operator==(const Vector2 &other) const {
            return x == other.x && y == other.y;
        }

        constexpr bool operator!=(const Vector2 &other) const {
            return x != other.x || y != other.y;
        }

        constexpr void Clear() {
            x = 0;
            y = 0;
        }

        constexpr T Dot(const Vector2 &other) const {
            return x * other.x + y * other.y;
        }

        constexpr T Cross(const Vector2 &other) const {
            return x * other.y - y * other.x;
        }

        T x;
        T y;
    };

    typedef Vector2<float> FVector2;
    typedef Vector2<unsigned int> UVector2;
}

#endif //SYSTEM_HPP

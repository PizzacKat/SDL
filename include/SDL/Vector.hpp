#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <type_traits>
#include <SDL3/SDL_rect.h>

namespace SDL {
    template <typename T = int>
    struct Vector2 {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "T must be a number type");

        Vector2(): x(0), y(0) {

        }

        Vector2(T x, T y): x(x), y(y) {

        }

        template <typename N>
        Vector2(const Vector2<N> &other): x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {

        }

        Vector2(SDL_Point point): x(static_cast<T>(point.x)), y(static_cast<T>(point.y)) {

        }

        Vector2(SDL_FPoint point): x(static_cast<T>(point.x)), y(static_cast<T>(point.y)) {

        }

        operator SDL_Point() const {
            return SDL_Point(static_cast<int>(x), static_cast<int>(y));
        }

        operator SDL_FPoint() const {
            return SDL_FPoint(static_cast<float>(x), static_cast<float>(y));
        }

        Vector2 operator+(const Vector2 &other) const {
            return Vector2(this->x + other.x, this->y + other.y);
        }

        Vector2 operator-(const Vector2 &other) const {
            return Vector2(this->x - other.x, this->y - other.y);
        }

        Vector2 operator*(const Vector2 &other) const {
            return Vector2(this->x * other.x, this->y * other.y);
        }

        Vector2 operator*(T other) const {
            return Vector2(this->x * other, this->y * other);
        }

        Vector2 operator/(T other) const {
            return Vector2(this->x / other, this->y / other);
        }

        [[nodiscard]] T length() const {
            return sqrt(this->x * this->x + this->y * this->y);
        }

        [[nodiscard]] T lengthSq() const {
            return this->x * this->x + this->y * this->y;
        }

        [[nodiscard]] Vector2 normalized() const {
            return Vector2(this->x / this->length(), this->y / this->length());
        }

        bool operator==(const Vector2 &other) const {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vector2 &other) const {
            return x != other.x || y != other.y;
        }

        T x;
        T y;
    };

    typedef Vector2<float> FVector2;
    typedef Vector2<unsigned int> UVector2;
}

#endif //SYSTEM_HPP

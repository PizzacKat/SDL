#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <cmath>
#include <type_traits>
#include <SDL3/SDL_rect.h>

namespace SDL {
    template <typename T = int>
    struct Vector2 {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "const T must be a number type");

        constexpr Vector2(): x(0), y(0) {

        }

        constexpr Vector2(const T x, const T y): x(x), y(y) {

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
            return {x + other.x, y + other.y};
        }

        constexpr Vector2 operator-(const Vector2 &other) const {
            return {x - other.x, y - other.y};
        }

        constexpr Vector2 operator*(const Vector2 &other) const {
            return {x * other.x, y * other.y};
        }

        constexpr Vector2 operator*(const T other) const {
            return {x * other, y * other};
        }

        constexpr Vector2 operator/(const T other) const {
            return {x / other, y / other};
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
            return {x * x / LengthSq(),  y * y / LengthSq()};
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

    template <typename T = int>
    struct Vector3 {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "const T must be a number type");

        constexpr Vector3(): x(0), y(0), z(0) {

        }

        constexpr Vector3(const T x, const T y, const T z): x(x), y(y), z(z) {

        }

        template <typename N>
        constexpr Vector3(const Vector3<N> &other): x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {

        }

        constexpr Vector3(const Vector2<T> &vec2, const T z = 0): x(static_cast<T>(vec2.x)), y(static_cast<T>(vec2.y)), z(z) {

        }

        constexpr Vector3 operator+(const Vector3 &other) const {
            return {x + other.x, y + other.y, z + other.z};
        }

        constexpr Vector3 operator-(const Vector3 &other) const {
            return {x - other.x, y - other.y, z - other.z};
        }

        constexpr Vector3 operator*(const T other) const {
            return {x * other, y * other, z * other};
        }

        constexpr Vector3 operator/(const T other) const {
            return {x / other, y / other, z / other};
        }

        constexpr Vector3 &operator+=(const Vector3 &other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        constexpr Vector3 &operator-=(const Vector3 &other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        constexpr Vector3 &operator*=(const T other) {
            x *= other;
            y *= other;
            z *= other;
            return *this;
        }

        constexpr Vector3 &operator/=(const T other) {
            x /= other;
            y /= other;
            z /= other;
            return *this;
        }

        [[nodiscard]] constexpr T Length() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        [[nodiscard]] constexpr T LengthSq() const {
            return x * x + y * y + z * z;
        }

        [[nodiscard]] constexpr Vector3 Normalized() const {
            return {x * x / LengthSq(), y * y / LengthSq(), z * z / LengthSq()};
        }

        constexpr bool operator==(const Vector3 &other) const {
            return x == other.x && y == other.y && z == other.z;
        }

        constexpr bool operator!=(const Vector3 &other) const {
            return x != other.x || y != other.y || z != other.z;
        }

        constexpr void Clear() {
            x = 0;
            y = 0;
            z = 0;
        }

        constexpr T Dot(const Vector3 &other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        constexpr Vector3 Cross(const Vector3 &other) const {
            return {y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x};
        }

        constexpr explicit operator Vector2<T>() const {
            return {x, y};
        }

        T x;
        T y;
        T z;
    };

    typedef Vector3<float> FVector3;
    typedef Vector3<unsigned int> UVector3;

    template <typename T = int>
    struct Vector4 {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "const T must be a number type");

        constexpr Vector4(): x(0), y(0), z(0), w(0) {

        }

        constexpr Vector4(const T x, const T y, const T z, const T w): x(x), y(y), z(z), w(w) {

        }

        template <typename N>
        constexpr Vector4(const Vector4<N> &other): x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(static_cast<T>(other.w)) {

        }

        constexpr Vector4(const Vector2<T> &vec2, const T z = 0, const T w = 0): x(static_cast<T>(vec2.x)), y(static_cast<T>(vec2.y)), z(z), w(w) {

        }

        constexpr Vector4(const Vector3<T> &vec3, const T w = 0): x(static_cast<T>(vec3.x)), y(static_cast<T>(vec3.y)), z(static_cast<T>(vec3.z)), w(w) {

        }

        constexpr Vector4 operator+(const Vector4 &other) const {
            return {x + other.x, y + other.y, z + other.z, w + other.w};
        }

        constexpr Vector4 operator-(const Vector4 &other) const {
            return {x - other.x, y - other.y, z - other.z, w - other.w};
        }

        constexpr Vector4 operator*(const T other) const {
            return {x * other, y * other, z * other, w * other};
        }

        constexpr Vector4 operator/(const T other) const {
            return {x / other, y / other, z / other, w / other};
        }

        constexpr Vector4 &operator+=(const Vector4 &other) {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }

        constexpr Vector4 &operator-=(const Vector4 &other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return *this;
        }

        constexpr Vector4 &operator*=(const T other) {
            x *= other;
            y *= other;
            z *= other;
            w /= other;
            return *this;
        }

        constexpr Vector4 &operator/=(const T other) {
            x /= other;
            y /= other;
            z /= other;
            w /= other;
            return *this;
        }

        [[nodiscard]] constexpr T Length() const {
            return std::sqrt(x * x + y * y + z * z + w * w);
        }

        [[nodiscard]] constexpr T LengthSq() const {
            return x * x + y * y + z * z + w * w;
        }

        [[nodiscard]] constexpr Vector4 Normalized() const {
            return {x * x / LengthSq(), y * y / LengthSq(), z * z / LengthSq(), w * w / LengthSq()};
        }

        constexpr bool operator==(const Vector4 &other) const {
            return x == other.x && y == other.y && z == other.z && w == other.w;
        }

        constexpr bool operator!=(const Vector4 &other) const {
            return x != other.x || y != other.y || z != other.z || w != other.w;
        }

        constexpr void Clear() {
            x = 0;
            y = 0;
            z = 0;
            w = 0;
        }

        constexpr T Dot(const Vector4 &other) const {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        constexpr explicit operator Vector3<T>() const {
            return {x, y, z};
        }

        T x;
        T y;
        T z;
        T w;
    };

    typedef Vector4<float> FVector4;
    typedef Vector4<unsigned int> UVector4;
}

#endif //SYSTEM_HPP

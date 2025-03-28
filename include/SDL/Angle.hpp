#ifndef RANGEDVALUE_HPP
#define RANGEDVALUE_HPP
#include <cmath>
#include <SDL3/SDL_stdinc.h>

namespace SDL {
    class Angle {
    public:
        constexpr Angle(): _angle(0.0f) {

        }

        [[nodiscard]] constexpr float AsRadians() const {
            return _angle;
        }

        [[nodiscard]] constexpr float AsDegrees() const {
            return _angle * 180.0f / SDL_PI_F;
        }

        constexpr Angle operator+(const Angle &other) const {
            return _angle + other._angle;
        }

        constexpr Angle &operator+=(const Angle &other) {
            _angle += other._angle;
            return *this;
        }

        constexpr Angle operator-(const Angle &other) const {
            return _angle - other._angle;
        }

        constexpr Angle &operator-=(const Angle &other) {
            _angle -= other._angle;
            return *this;
        }

        constexpr Angle operator*(const Angle &other) const {
            return _angle * other._angle;
        }

        constexpr Angle &operator*=(const Angle &other) {
            _angle *= other._angle;
            return *this;
        }

        constexpr Angle operator*(const float other) const {
            return _angle * other;
        }

        constexpr Angle &operator*=(const float other) {
            _angle *= other;
            return *this;
        }

        constexpr Angle operator/(const Angle &other) const {
            return _angle / other._angle;
        }

        constexpr Angle &operator/=(const Angle &other) {
            _angle /= other._angle;
            return *this;
        }

        constexpr Angle operator/(const float other) const {
            return _angle / other;
        }

        constexpr Angle &operator/=(const float other) {
            _angle /= other;
            return *this;
        }

        constexpr Angle operator-() const {
            return -_angle;
        }

        constexpr bool operator==(const Angle &other) const {
            return _angle == other._angle;
        }

        constexpr bool operator!=(const Angle &other) const {
            return _angle != other._angle;
        }

        [[nodiscard]] Angle Wrap() const {
            return SDL_fmodf(_angle, SDL_PI_F * 2);
        }
    private:
        constexpr Angle(const float angle): _angle(angle) {

        }

        friend constexpr Angle FromRadians(float radians);
        friend constexpr Angle FromDegrees(float degrees);

        float _angle;
    };

    constexpr Angle FromRadians(const float radians) {
        return radians;
    }

    constexpr Angle FromDegrees(const float degrees) {
        return degrees * SDL_PI_F / 180.0f;
    }

    constexpr Angle operator""_Rad(const long double angle) {
        return FromRadians(static_cast<float>(angle));
    }

    constexpr Angle operator""_Deg(const long double angle) {
        return FromDegrees(static_cast<float>(angle));
    }
}

#endif //RANGEDVALUE_HPP

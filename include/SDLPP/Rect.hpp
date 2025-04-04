#ifndef RECT_HPP
#define RECT_HPP

#include <algorithm>
#include <optional>
#include "Vector.hpp"

namespace SDL {
    template <typename T = int>
    struct Rect {
        Rect()= default;

        template <typename N>
        Rect(const Rect<N> &other): position(other.position), size(other.size) {

        }

        Rect(const Vector2<T> position, const Vector2<T> size): position(position), size(size) {

        }

        Rect(const T x, const T y, const T w, const T h): position(x, y), size(w, h) {

        }

        Rect(const SDL_FRect rect): Rect(Vector2<T>(static_cast<T>(rect.x), static_cast<T>(rect.y)), Vector2<T>(static_cast<T>(rect.w), static_cast<T>(rect.h))) {

        }

        Rect(const SDL_Rect rect): Rect(Vector2<T>(static_cast<T>(rect.x), static_cast<T>(rect.y)), Vector2<T>(static_cast<T>(rect.w), static_cast<T>(rect.h))) {

        }

        operator SDL_FRect() const {
            return SDL_FRect(static_cast<float>(position.x), static_cast<float>(position.y), static_cast<float>(size.x), static_cast<float>(size.y));
        }

        operator SDL_Rect() const {
            return SDL_Rect(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y));
        }

        bool operator==(const Rect &other) const {
            return position == other.position && size == other.size;
        }

        bool operator!=(const Rect &other) const {
            return position != other.position || size != other.size;
        }

        [[nodiscard]] bool Contains(const Vector2<T> &other) const {
            return position.x < other.x && position.y < other.y && other.x < position.x + size.x && other.y < position.y + size.y;
        }

        [[nodiscard]] bool Intersects(const Rect &other) const {
            const T left = std::max(position.x, other.position.x);
            const T top = std::max(position.y, other.position.y);
            const T right = std::min(position.x + size.x, other.position.x + other.size.x);
            const T bottom = std::min(position.y + size.y, other.position.y + other.size.y);
            return left < right && top < bottom;
        }

        [[nodiscard]] std::optional<Rect> Intersection(const Rect &other) const {
            const T left = std::max(position.x, other.position.x);
            const T top = std::max(position.y, other.position.y);
            const T right = std::min(position.x + size.x, other.position.x + other.size.x);
            const T bottom = std::min(position.y + size.y, other.position.y + other.size.y);

            if (left < right && top < bottom)
                return Rect(left, top, right - left, bottom - top);
            return std::nullopt;
        }

        std::optional<Rect> operator&(const Rect &other) const {
            return Intersection(other);
        }

        Vector2<T> position;
        Vector2<T> size;
    };

    typedef Rect<float> FRect;
}

#endif //RECT_HPP

#include "SDLPP/Shapes.hpp"

namespace SDL::Shapes {
    Rectangle::Rectangle() = default;

    Rectangle::Rectangle(const FVector2 &size): _size(size) {
        Recompute();
    }

    void Rectangle::SetSize(const FVector2 &size) {
        _size = size;
        Recompute();
    }

    const FVector2 &Rectangle::GetSize() const {
        return _size;
    }

    FVector2 Rectangle::GetCenter() const {
        return _size / 2.0f;
    }

    FVector2 Rectangle::GetPoint(const std::size_t i) const {
        switch (i) {
            case 0:
                return {0, 0};
            case 1:
                return {_size.x, 0};
            case 2:
                return _size;
            case 3:
                return {0, _size.y};
            default:
                return {};
        }
    }

    std::size_t Rectangle::GetPointCount() const {
        return 4;
    }

    Circle::Circle()= default;

    Circle::Circle(const float radius, const unsigned int points): _radius(radius), _points(points) {
        Recompute();
    }

    void Circle::SetRadius(const float radius) {
        _radius = radius;
        Recompute();
    }

    float Circle::GetRadius() const {
        return _radius;
    }

    void Circle::SetPoints(const unsigned int points) {
        _points = points;
        Recompute();
    }

    unsigned int Circle::GetPoints() const {
        return _points;
    }

    FVector2 Circle::GetCenter() const {
        return {_radius, _radius};
    }

    FVector2 Circle::GetPoint(const std::size_t i) const {
        const float a = static_cast<float>(i) / static_cast<float>(_points) * std::numbers::pi_v<float> * 2;
        return FVector2(std::cos(a) * _radius, std::sin(a) * _radius) + FVector2(_radius, _radius);
    }

    std::size_t Circle::GetPointCount() const {
        return _points;
    }
}

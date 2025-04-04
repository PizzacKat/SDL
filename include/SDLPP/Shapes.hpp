#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <complex>

#include "Renderer.hpp"
#include "Transformable.hpp"

namespace SDL::Shapes {
    class Rectangle : public Transformable {
    public:
        Rectangle();
        explicit Rectangle(const FVector2 &size);

        void SetSize(const FVector2 &size);
        [[nodiscard]] const FVector2 &GetSize() const;
    private:
        [[nodiscard]] FVector2 GetCenter() const override;
        [[nodiscard]] FVector2 GetPoint(std::size_t i) const override;
        [[nodiscard]] std::size_t GetPointCount() const override;

        FVector2 _size;
    };

    class Circle : public Transformable {
    public:
        Circle();
        explicit Circle(float radius, unsigned int points = 30);

        void SetRadius(float radius);
        [[nodiscard]] float GetRadius() const;
        void SetPoints(unsigned int points);
        [[nodiscard]] unsigned int GetPoints() const;
    private:
        [[nodiscard]] FVector2 GetCenter() const override;
        [[nodiscard]] FVector2 GetPoint(std::size_t i) const override;
        [[nodiscard]] std::size_t GetPointCount() const override;

        float _radius = 0.0f;
        unsigned int _points = 30;
    };
}

#endif //SHAPES_HPP

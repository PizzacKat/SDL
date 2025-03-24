#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <complex>

#include "Drawable.hpp"
#include "Rect.hpp"
#include "Renderer.hpp"

namespace SDL::Shapes {
    class Rectangle : public Drawable {
    public:
        Rectangle();
        Rectangle(const FVector2 &position, const FVector2 &size);
        Rectangle(float x, float y, float w, float h);
        explicit Rectangle(const Rect<float> &rect);

        void SetPosition(FVector2 position);
        [[nodiscard]] const FVector2 &GetPosition() const;
        void SetSize(FVector2 size);
        [[nodiscard]] const FVector2 &GetSize() const;
        void SetRect(FRect rect);
        [[nodiscard]] const FRect &GetRect() const;
        void SetColor(Color color);
        [[nodiscard]] const Color &GetColor() const;

        [[nodiscard]] bool Intersects(const Rectangle &other) const;
        [[nodiscard]] bool Intersects(const FRect &other) const;
        [[nodiscard]] std::optional<Rectangle> Intersection(const Rectangle &other) const;
        [[nodiscard]] std::optional<Rectangle> Intersection(const FRect &other) const;
    private:
        void Recompute();

        FRect _rect;
        Color _color;
        SDL_Vertex _vertices[4];
        constexpr static int indices[6] = {0, 1, 2, 2, 3, 1};
        void Draw(Renderer &renderer) const override;
    };

    class Circle : public Drawable {
    public:
        Circle();
        explicit Circle(float radius, int detail = 32);

        void SetPosition(const FVector2 &position);
        [[nodiscard]] FVector2 GetPosition() const;
        void SetColor(Color color);
        [[nodiscard]] Color GetColor() const;
        void SetRadius(float radius);
        [[nodiscard]] float GetRadius() const;
        void SetDetail(int detail);
        [[nodiscard]] int GetDetail() const;

    private:
        void Recompute();

        int _detail;
        float _radius;
        Color _color;
        FVector2 _position;
        VertexBuffer _vertices;

        void Draw(Renderer &renderer) const override;
    };
}

#endif //SHAPES_HPP

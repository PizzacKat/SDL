#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Drawable.hpp"
#include "Rect.hpp"
#include "Vertex.hpp"

namespace SDL {
    class Shape : public Drawable {
    public:
        Shape();

        void SetColor(const Color &color);
        [[nodiscard]] const Color &GetColor() const;

        [[nodiscard]] virtual FVector2 GetPoint(std::size_t i) const= 0;
        [[nodiscard]] virtual std::size_t GetPointCount() const= 0;
        [[nodiscard]] FRect GetBoundingBox() const;
        [[nodiscard]] virtual FVector2 GetCenter() const= 0;

    protected:
        virtual void Transform(FVector2 &v) const;
        void Recompute();

        void Draw(Renderer &renderer) const override;
    private:
        Color _color;
        VertexBuffer _vertices;
        FRect _bounds;
    };
}

#endif //SHAPE_HPP

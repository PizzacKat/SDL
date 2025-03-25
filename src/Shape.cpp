#include "SDL/Shape.hpp"

#include <iostream>

#include "SDL/Renderer.hpp"

namespace SDL {
    Shape::Shape()= default;

    void Shape::SetColor(const Color &color) {
        _color = color;
        Recompute();
    }

    const Color &Shape::GetColor() const {
        return _color;
    }

    FRect Shape::GetBoundingBox() const {
        return _bounds;
    }

    void Shape::Transform(FVector2 &v) const {

    }

    void Shape::Recompute() {
        _vertices.ClearIndices();
        _vertices.Resize(GetPointCount() + 1);

        FVector2 center = GetCenter();
        Transform(center);
        _vertices.GetVertex(0) = Vertex(center, _color);

        FVector2 minBound = center;
        FVector2 maxBound = center;

        for (std::size_t i = 0; i < GetPointCount(); ++i) {
            FVector2 val = GetPoint(i);
            Transform(val);
            _vertices.GetVertex(i + 1) = Vertex(val, _color);
            if (i > 0) {
                _vertices.Add(0);
                _vertices.Add(static_cast<int>(i));
                _vertices.Add(static_cast<int>(i) + 1);
            }
            if (val.x < minBound.x)
                minBound.x = val.x;
            if (val.y < minBound.y)
                minBound.y = val.y;
            if (val.x > maxBound.x)
                maxBound.x = val.x;
            if (val.y > maxBound.y)
                maxBound.y = val.y;
        }

        _bounds = {minBound, maxBound - minBound};

        if (GetPointCount() > 0) {
            _vertices.Add(0);
            _vertices.Add(1);
            _vertices.Add(static_cast<int>(GetPointCount()));
        }
    }

    void Shape::Draw(Renderer &renderer) const {
        renderer.Draw(_vertices);
    }
}

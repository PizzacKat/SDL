#include "SDL/Shapes.hpp"

#include <iostream>

namespace SDL::Shapes {
    Rectangle::Rectangle() = default;

    Rectangle::Rectangle(const FRect &rect): _rect(rect) {

    }

    Rectangle::Rectangle(const FVector2 &position, const FVector2 &size): _rect(position, size) {

    }

    Rectangle::Rectangle(const float x, const float y, const float w, const float h): _rect(x, y, w, h) {

    }

    void Rectangle::SetPosition(const FVector2 position) {
        _rect.position = position;
        Recompute();
    }

    const FVector2 &Rectangle::GetPosition() const {
        return _rect.position;
    }

    void Rectangle::SetSize(const FVector2 size) {
        _rect.size = size;
        Recompute();
    }

    const FVector2 &Rectangle::GetSize() const {
        return _rect.size;
    }

    void Rectangle::SetColor(const Color color) {
        _color = color;
        Recompute();
    }

    const Color &Rectangle::GetColor() const {
        return _color;
    }

    void Rectangle::SetRect(const FRect rect) {
        _rect = rect;
        Recompute();
    }

    const FRect &Rectangle::GetRect() const {
        return _rect;
    }

    bool Rectangle::Intersects(const Rectangle &other) const {
        return _rect.Intersects(other._rect);
    }

    bool Rectangle::Intersects(const FRect &other) const {
        return _rect.Intersects(other);
    }

    std::optional<Rectangle> Rectangle::Intersection(const Rectangle &other) const {
        if (const std::optional<FRect> rect = _rect.Intersection(other._rect))
            return Rectangle(rect.value());
        return std::nullopt;
    }

    std::optional<Rectangle> Rectangle::Intersection(const FRect &other) const {
        if (const std::optional<FRect> rect = _rect.Intersection(other))
            return Rectangle(rect.value());
        return std::nullopt;
    }

    void Rectangle::Recompute() {
        const SDL_FColor color = FColor(_color);
        _vertices[0].position = _rect.position;
        _vertices[0].color = color;
        _vertices[1].position = _rect.position + FVector2(_rect.size.x, 0.0f);
        _vertices[1].color = color;
        _vertices[2].position = _rect.position + FVector2(0.0f, _rect.size.y);
        _vertices[2].color = color;
        _vertices[3].position = _rect.position + _rect.size;
        _vertices[3].color = color;
    }

    void Rectangle::Draw(Renderer &renderer) const {
        renderer.Draw(_vertices, 4, indices, 6);
    }

    Circle::Circle(): _detail(0), _radius(0) {

    }

    Circle::Circle(const float radius, const int detail): _detail(detail), _radius(radius) {
        Recompute();
    }

    void Circle::SetPosition(const FVector2 &position) {
        _position = position;
        Recompute();
    }

    FVector2 Circle::GetPosition() const {
        return _position;
    }

    void Circle::SetRadius(const float radius) {
        _radius = radius;
        Recompute();
    }

    void Circle::SetColor(const Color color) {
        _color = color;
        Recompute();
    }

    Color Circle::GetColor() const {
        return _color;
    }

    float Circle::GetRadius() const {
        return _radius;
    }

    void Circle::SetDetail(const int detail) {
        _detail = detail;
        Recompute();
    }

    int Circle::GetDetail() const {
        return _detail;
    }

    void Circle::Recompute() {
        _vertices.Clear();
        Vertex vertex;
        vertex.position = _position;
        vertex.color = _color;
        _vertices.Add(vertex);
        for (int i = 0; i < _detail; i++) {
            vertex.position = _position + FVector2(static_cast<float>(std::cos(2 * M_PI * i / _detail)), static_cast<float>(std::sin(2 * M_PI * i / _detail))) * _radius;
            _vertices.Add(vertex);
            if (_vertices.VertexCount() > 2) {
                _vertices.Add(0);
                _vertices.Add(static_cast<int>(_vertices.VertexCount()) - 2);
                _vertices.Add(static_cast<int>(_vertices.VertexCount()) - 1);
            }
        }
        _vertices.Add(0);
        _vertices.Add(1);
        _vertices.Add(static_cast<int>(_vertices.VertexCount()) - 1);
    }

    void Circle::Draw(Renderer &renderer) const {
        SDL_RenderGeometry(renderer, nullptr, _vertices.Vertices(), static_cast<int>(_vertices.VertexCount()), _vertices.Indices(), static_cast<int>(_vertices.IndexCount()));
    }
}

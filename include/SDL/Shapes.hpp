#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "Drawable.hpp"
#include "Rect.hpp"
#include "Renderer.hpp"

namespace SDL::Shapes {
    class Rectangle : public Drawable {
    public:
        Rectangle()= default;

        Rectangle(const FVector2 &position, const FVector2 &size): _position(position), _size(size) {

        }

        Rectangle(const float x, const float y, const float w, const float h): _position(x, y), _size(w, h) {

        }

        explicit Rectangle(const Rect<float> &rect): Rectangle(rect.position, rect.size) {

        }

        void SetPosition(const FVector2 &position) {
            _position = position;
        }

        [[nodiscard]] const FVector2 &GetPosition() const {
            return _position;
        }

        void SetSize(const FVector2 &size) {
            _size = size;
        }

        [[nodiscard]] const FVector2 &GetSize() const {
            return _size;
        }

        void SetColor(const Color &color) {
            _color = color;
        }

        [[nodiscard]] const Color &GetColor() const {
            return _color;
        }
    private:
        void Draw(Renderer &renderer) const override {
            const SDL_Vertex vertices[4] = {
                SDL_Vertex{_position, FColor(_color)},
                SDL_Vertex{_position + FVector2(_size.x, 0), FColor(_color)},
                SDL_Vertex{_position + FVector2(0, _size.y), FColor(_color)},
                SDL_Vertex{_position + _size, FColor(_color)},
            };
            const int indices[6] = {0, 2, 1, 1, 2, 3};
            renderer.Draw(vertices, 4, indices, 6);
        }

        FVector2 _position;
        FVector2 _size;
        Color _color;
    };
}

#endif //SHAPES_HPP

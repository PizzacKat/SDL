#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "Drawable.hpp"
#include "Rect.hpp"
#include "Renderer.hpp"

namespace SDL::Shapes {
    class Rectangle : public Drawable {
    public:
        Rectangle()= default;

        Rectangle(const FVector2 &position, const FVector2 &size): position(position), size(size) {

        }

        Rectangle(const float x, const float y, const float w, const float h): position(x, y), size(w, h) {

        }

        explicit Rectangle(const Rect<float> &rect): Rectangle(rect.position, rect.size) {

        }

        FVector2 position;
        FVector2 size;
        Color color;
    private:
        void Draw(Renderer &renderer) const override {
            const SDL_Vertex vertices[4] = {
                SDL_Vertex{position, FColor(color)},
                SDL_Vertex{position + FVector2(size.x, 0), FColor(color)},
                SDL_Vertex{position + FVector2(0, size.y), FColor(color)},
                SDL_Vertex{position + size, FColor(color)},
            };
            const int indices[6] = {0, 2, 1, 1, 2, 3};
            renderer.Draw(vertices, 4, indices, 6);
        }
    };
}

#endif //SHAPES_HPP

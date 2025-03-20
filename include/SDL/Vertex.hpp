#ifndef VERTEX_HPP
#define VERTEX_HPP
#include <cstddef>
#include <vector>
#include <SDL3/SDL_render.h>

#include "Color.hpp"
#include "Vector.hpp"

namespace SDL {
    class Vertex {
    public:
        Vertex()= default;

        Vertex(const FVector2 &position, const Color &color, const FVector2 &textureCoord = {}): position(position), color(color), texCoord(textureCoord) {

        }

        Vertex(const SDL_Vertex &vertex): position(vertex.position), color(vertex.color), texCoord(vertex.tex_coord) {

        }

        operator SDL_Vertex() const {
            return {position, color, texCoord};
        }

        FVector2 position;
        FColor color;
        FVector2 texCoord;
    };

    class VertexBuffer {
    public:
        VertexBuffer()= default;

        void Add(const Vertex &vertex, const bool add_index = false) {
            _vertices.emplace_back(vertex);
            if (add_index)
                _indices.emplace_back(static_cast<int>(_vertices.size() - 1));
        }

        void Add(int index) {
            _indices.emplace_back(index);
        }

        [[nodiscard]] std::size_t VertexCount() const {
            return _vertices.size();
        }

        [[nodiscard]] const SDL_Vertex *Vertices() const {
            return _vertices.data();
        }

        [[nodiscard]] std::size_t IndexCount() const {
            return _indices.size();
        }

        [[nodiscard]] const int *Indices() const {
            return _indices.data();
        }
    private:
        std::vector<SDL_Vertex> _vertices;
        std::vector<int> _indices;
    };
}

#endif //VERTEX_HPP

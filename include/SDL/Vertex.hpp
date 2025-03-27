#ifndef VERTEX_HPP
#define VERTEX_HPP
#include <cstddef>
#include <vector>
#include <SDL3/SDL_render.h>

#include "Color.hpp"
#include "Vector.hpp"

namespace SDL {
    struct Vertex {
        Vertex();

        Vertex(const FVector2 &position, const Color &color, const FVector2 &textureCoord = {});
        Vertex(const SDL_Vertex &vertex);
        operator SDL_Vertex() const;

        FVector2 position;
        FColor color;
        FVector2 texCoord;
    };

    class VertexBuffer {
    public:
        VertexBuffer();

        void Clear();
        void ClearVertices();
        void ClearIndices();

        void Add(const Vertex &vertex, bool add_index = false);
        void Add(int index);
        void Add(std::initializer_list<int> indices);

        void Resize(std::size_t size);

        [[nodiscard]] SDL_Vertex &GetVertex(std::size_t i);
        [[nodiscard]] const SDL_Vertex &GetVertex(std::size_t i) const;

        [[nodiscard]] const int &GetIndex(std::size_t i) const;

        [[nodiscard]] std::size_t VertexCount() const;
        [[nodiscard]] const SDL_Vertex *Vertices() const;
        [[nodiscard]] std::size_t IndexCount() const;
        [[nodiscard]] const int *Indices() const;
    private:
        std::vector<SDL_Vertex> _vertices;
        std::vector<int> _indices;
    };
}

#endif //VERTEX_HPP

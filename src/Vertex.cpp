#include "SDL/Vertex.hpp"

SDL::Vertex::Vertex() = default;

SDL::Vertex::Vertex(const FVector2 &position, const Color &color, const FVector2 &textureCoord): position(position), color(color), texCoord(textureCoord) {

}

SDL::Vertex::Vertex(const SDL_Vertex &vertex): position(vertex.position), color(vertex.color), texCoord(vertex.tex_coord) {

}

SDL::Vertex::operator SDL_Vertex() const {
    return {position, color, texCoord};
}

SDL::VertexBuffer::VertexBuffer() = default;

void SDL::VertexBuffer::Clear() {
    _vertices.clear();
    _indices.clear();
}

void SDL::VertexBuffer::Add(const Vertex &vertex, const bool add_index) {
    _vertices.emplace_back(vertex);
    if (add_index)
        _indices.emplace_back(static_cast<int>(_vertices.size() - 1));
}

void SDL::VertexBuffer::Add(int index) {
    _indices.emplace_back(index);
}

std::size_t SDL::VertexBuffer::VertexCount() const {
    return _vertices.size();
}

const SDL_Vertex *SDL::VertexBuffer::Vertices() const {
    return _vertices.data();
}

std::size_t SDL::VertexBuffer::IndexCount() const {
    return _indices.size();
}

const int *SDL::VertexBuffer::Indices() const {
    return _indices.data();
}

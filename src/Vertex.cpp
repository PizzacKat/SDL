#include "SDLPP/Vertex.hpp"

namespace SDL {
    Vertex::Vertex() = default;

    Vertex::Vertex(const FVector2 &position, const Color &color, const FVector2 &textureCoord): position(position), color(color), texCoord(textureCoord) {

    }

    Vertex::Vertex(const SDL_Vertex &vertex): position(vertex.position), color(vertex.color), texCoord(vertex.tex_coord) {

    }

    Vertex::operator SDL_Vertex() const {
        return {position, color, texCoord};
    }

    VertexBuffer::VertexBuffer() = default;

    void VertexBuffer::Clear() {
        _vertices.clear();
        _indices.clear();
    }

    void VertexBuffer::ClearVertices() {
        _vertices.clear();
    }

    void VertexBuffer::ClearIndices() {
        _indices.clear();
    }

    void VertexBuffer::Add(const Vertex &vertex, const bool add_index) {
        _vertices.emplace_back(vertex);
        if (add_index)
            _indices.emplace_back(static_cast<int>(_vertices.size() - 1));
    }

    void VertexBuffer::Add(int index) {
        _indices.emplace_back(index);
    }

    void VertexBuffer::Add(const std::initializer_list<int> indices) {
        _indices.insert(_indices.end(), indices.begin(), indices.end());
    }

    void VertexBuffer::Resize(const std::size_t size) {
        _vertices.resize(size);
    }

    SDL_Vertex &VertexBuffer::GetVertex(const std::size_t i) {
        return _vertices[i];
    }

    const SDL_Vertex &VertexBuffer::GetVertex(const std::size_t i) const {
        return _vertices[i];
    }

    const int &VertexBuffer::GetIndex(const std::size_t i) const {
        return _indices[i];
    }

    std::size_t VertexBuffer::VertexCount() const {
        return _vertices.size();
    }

    const SDL_Vertex *VertexBuffer::Vertices() const {
        return _vertices.data();
    }

    std::size_t VertexBuffer::IndexCount() const {
        return _indices.size();
    }

    const int *VertexBuffer::Indices() const {
        if (_indices.empty())
            return nullptr;
        return _indices.data();
    }
}

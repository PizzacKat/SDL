#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <memory>
#include "Window.hpp"

#include "Color.hpp"
#include "Drawable.hpp"
#include "Properties.hpp"
#include "Rect.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"
#include "APIObject.hpp"

namespace SDL {
    class Renderer {
    public:
        Renderer(Renderer &&renderer) noexcept;
        Renderer &operator=(Renderer &&renderer) noexcept;

        explicit Renderer(class Window &window);
        Renderer(const class Window &window, const std::string &name);
        explicit Renderer(const Properties &properties);

        Renderer(SDL_Renderer *renderer);
        Renderer(SDL_Renderer *renderer, Borrowed borrowed);

        [[nodiscard]] Window GetWindow() const;

        [[nodiscard]] Texture Target() const;

        void SetTarget(std::nullptr_t);
        void SetTarget(Texture &texture);

        [[nodiscard]] SDL_Renderer *Get() const;
        operator SDL_Renderer *() const;

        void SetDrawColor(const Color &color);
        [[nodiscard]] Color GetDrawColor() const;

        void Clear();
        void Clear(const Color &color);

        void Draw(const SDL_Vertex *vertices, int vertexCount, const Texture &texture = nullptr);
        void Draw(const SDL_Vertex *vertices, int vertexCount, const int *indices, int indexCount, const Texture &texture = nullptr);
        void Draw(const VertexBuffer &vertices, const Texture &texture = nullptr);
        void Draw(const Drawable &drawable);

        void SetViewport(const std::optional<Rect<>> &rect);
        [[nodiscard]] Rect<> GetViewport() const;

        void SetClipRect(const std::optional<Rect<>> &rect);
        [[nodiscard]] Rect<> GetClipRect() const;

        void SetVSync(bool enable);
        [[nodiscard]] bool GetVSync() const;

        void Display();

        [[nodiscard]] Properties GetProperties() const;
    private:
        Object::APIObject<SDL_Renderer *> _renderer;
    };
}

#endif //RENDERER_HPP

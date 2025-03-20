#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <memory>
#include <SDL3/SDL_render.h>
#include <SDL/Window.hpp>

#include "Color.hpp"
#include "Drawable.hpp"
#include "Vector.hpp"
#include "Vertex.hpp"

namespace SDL {
    class Renderer;

    class Texture {
    public:
        Texture();
        Texture(const std::nullptr_t);
        Texture(SDL_Texture *texture);

        void LoadFile(const Renderer &renderer, const std::string &file);

        [[nodiscard]] FVector2 GetSize() const;
        [[nodiscard]] SDL_Texture *Get() const;

        explicit operator bool() const;
        bool operator==(const std::nullptr_t) const;

        operator SDL_Texture *() const;
    private:
        std::shared_ptr<SDL_Texture> _texture = nullptr;
    };

    class Renderer {
    public:
        explicit Renderer(class Window &window);

        Renderer(class Window &window, const std::string &name);

        Renderer(Renderer &)= delete;
        Renderer &operator=(Renderer &)= delete;
        Renderer(Renderer &&renderer) noexcept;

        Renderer &operator=(Renderer &&renderer) noexcept;

        [[nodiscard]] class Window &Window() const;

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

        void Display();

        ~Renderer();

    private:
        class Window *_window;
        SDL_Renderer *_renderer;
    };
}

#endif //RENDERER_HPP

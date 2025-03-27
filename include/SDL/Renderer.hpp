#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <memory>
#include <SDL3/SDL_render.h>
#include <SDL/Window.hpp>

#include "Color.hpp"
#include "Drawable.hpp"
#include "Rect.hpp"
#include "Texture.hpp"
#include "Vector.hpp"
#include "Vertex.hpp"

namespace SDL {
    class Renderer {
    public:
        explicit Renderer(class Window &window);

        Renderer(class Window &window, const std::string &name);

        Renderer(Renderer &)= delete;
        Renderer &operator=(Renderer &)= delete;
        Renderer(Renderer &&renderer) noexcept;

        Renderer &operator=(Renderer &&renderer) noexcept;

        [[nodiscard]] class Window &Window() const;
        [[nodiscard]] Texture *Target() const;

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

        void SetVSync(bool enable);
        [[nodiscard]] bool GetVSync() const;

        void Display();

        ~Renderer();

    private:
        Texture *_target = nullptr;
        class Window *_window;
        SDL_Renderer *_renderer;
    };
}

#endif //RENDERER_HPP

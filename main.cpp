#include <filesystem>
#include <iostream>
#include <memory>
#include <valarray>
#include <SDL3/SDL_gpu.h>

#include "SDL/Event.hpp"
#include "SDL/Renderer.hpp"
#include "SDL/Shapes.hpp"
#include "SDL/Window.hpp"
#include "SDL/Init.hpp"
#include "SDL/Rect.hpp"
#include "SDL/Timer.hpp"
#include "SDL/FramerateLimiter.hpp"
#include "SDL/Matrix.hpp"
#include "SDL/Transform.hpp"
#include "SDL/Transformable.hpp"

bool running = true;

SDL_InitFlags SDL::Init::flags = SDL_INIT_VIDEO;

template <typename T>
constexpr SDL::Vector2<T> Rotate90(const SDL::Vector2<T> &vector) {
    return {-vector.y, vector.x};
}

template <std::size_t N, typename Func, typename ...Args>
constexpr auto iterate(Func &&func, Args &&...args) {
    if constexpr (N == 1)
        return func(std::forward<Args>(args)...);
    else
        return iterate<N - 1>(func, func(std::forward<Args>(args)...));
}

int main() {
    SDL::Window window("Window!", {800, 600});
    SDL::Renderer renderer(window);
    SDL::FVector2 mouse;
    SDL::FramerateLimiter limiter(1000);

    SDL::Timer timer;
    float deltaTime = 0.0f;
    float time = 0.0f;

    SDL::Shapes::Circle shape(50);
    shape.SetColor(SDL::Color::White);
    shape.SetOrigin(SDL::FVector2(1.0f, 1.0f) * shape.GetRadius());
    shape.SetPosition(SDL::FVector2(1.0f, 1.0f) * shape.GetRadius());

    SDL::Shapes::Rectangle rect(shape.GetBoundingBox().size);
    rect.SetColor(SDL::Color::Blue);

    while (running) {
        while (const std::optional<SDL::Event> event = SDL::PollEvent()) {
            switch (event->type) {
                case SDL_EVENT_QUIT:
                    running = false;
                break;
                case SDL_EVENT_MOUSE_MOTION:
                    mouse.x = event->motion.x;
                    mouse.y = event->motion.y;
                break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                break;
                default:
                break;
            }
        }
        deltaTime = timer.Restart().AsSeconds();
        renderer.Clear(SDL::Color::Black);

        time += deltaTime;
        shape.SetRotation(time);

        rect.SetPosition(shape.GetBoundingBox().position);
        rect.SetSize(shape.GetBoundingBox().size);

        renderer.Draw(rect);
        renderer.Draw(shape);

        renderer.Display();
        SDL::FramerateType framerate = limiter.Update();
        window.SetTitle(std::to_string(framerate));
    }
    return 0;
}
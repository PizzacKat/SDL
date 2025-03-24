#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>
#include <valarray>

#include "SDL/Event.hpp"
#include "SDL/Renderer.hpp"
#include "SDL/Shapes.hpp"
#include "SDL/Window.hpp"
#include "SDL/Init.hpp"
#include "SDL/Rect.hpp"
#include "SDL/Timer.hpp"

bool running = true;

SDL_InitFlags SDL::Init::flags = SDL_INIT_VIDEO;

inline std::chrono::microseconds Now() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}

int main() {
    SDL::Window window("Window!", {800, 600});
    SDL::Renderer renderer(window);
    SDL::FVector2 mouse;

    SDL::Timer timer;
    float deltaTime = 0.0f;

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

        SDL::Shapes::Circle circle(16);
        SDL::Shapes::Rectangle rect1(16, 16, 32, 32);
        SDL::Shapes::Rectangle rect2(24, 24, 32, 32);

        circle.SetPosition({96, 96});
        circle.SetColor(SDL::Color::White);
        rect1.SetColor(SDL::Color::White);
        rect2.SetColor(SDL::Color::Red);

        renderer.Draw(circle);
        renderer.Draw(rect1);
        renderer.Draw(rect2);
        auto intersection = *rect1.Intersection(rect2);
        intersection.SetColor(SDL::Color::Blue);
        renderer.Draw(intersection);

        window.SetTitle(std::to_string(1.0f / deltaTime));

        renderer.Display();
    }
    return 0;
}
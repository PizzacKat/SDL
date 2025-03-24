#include <filesystem>
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
#include "SDL/FramerateLimiter.hpp"

bool running = true;

SDL_InitFlags SDL::Init::flags = SDL_INIT_VIDEO;

int main() {
    SDL::Window window("Window!", {800, 600});
    SDL::Renderer renderer(window);
    SDL::FVector2 mouse;
    SDL::FramerateLimiter limiter(60);

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

        circle.SetPosition({96, 96});
        circle.SetColor(SDL::Color::White);

        renderer.Draw(circle);

        renderer.Display();
        SDL::FramerateType framerate = limiter.Update();
        window.SetTitle(std::to_string(framerate));
    }
    return 0;
}
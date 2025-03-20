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

bool running = true;

SDL_InitFlags SDL::Init::flags = SDL_INIT_VIDEO;

inline std::chrono::microseconds Now() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}

int main() {
    SDL::Window window("Window!", {800, 600});
    SDL::Renderer renderer(window);
    SDL::FVector2 mouse;

    std::pair<SDL::FRect, SDL::Color> rects[8] = {
        {SDL::FRect(0, 0, 20, 40), SDL::Color::Black},
        {SDL::FRect(20, 0, 20, 40), SDL::Color::Black},
        {SDL::FRect(40, 0, 20, 40), SDL::Color::Black},
        {SDL::FRect(60, 0, 20, 40), SDL::Color::Black},
        {SDL::FRect(80, 0, 20, 40), SDL::Color::Black},
        {SDL::FRect(0, 0, 100, 100), SDL::Color::Red},
        {SDL::FRect(100, 100, 100, 100), SDL::Color::Green},
        {SDL::FRect(200, 200, 100, 100), SDL::Color::Blue},
    };

    SDL::FRect *grabbedRect = nullptr;
    SDL::FVector2 grabOffset;

    std::chrono::microseconds last = Now();

    std::size_t average;
    std::size_t probes = 0;

    while (running) {
        while (const std::optional<SDL::Event> event = SDL::PollEvent()) {
            switch (event->type) {
                case SDL_EVENT_QUIT:
                    running = false;
                break;
                case SDL_EVENT_MOUSE_MOTION:
                    mouse.x = event->motion.x;
                    mouse.y = event->motion.y;
                    if (grabbedRect != nullptr)
                        grabbedRect->position = mouse - grabOffset;
                break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    for (auto &[rect, color] : rects)
                        if (rect.Contains(mouse))
                            grabbedRect = &rect;
                    if (grabbedRect)
                        grabOffset = mouse - grabbedRect->position;
                break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    grabbedRect = nullptr;
                break;
                default:
                break;
            }
        }
        renderer.Clear(SDL::Color::Black);

        SDL::Shapes::Rectangle shape;

        for (const auto &[rect, color] : rects) {
            shape.SetPosition(rect.position);
            shape.SetSize(rect.size);
            shape.SetColor(color);
            renderer.Draw(shape);
        }

        std::function<void(SDL::FRect, SDL::Color, std::vector<const SDL::FRect *>)> CalculateIntersections = [&CalculateIntersections, &rects, &renderer](const SDL::FRect current, const SDL::Color color, std::vector<const SDL::FRect *> recent) {
            if (current == SDL::FRect()) {
                for (const auto &[rect, color] : rects) {
                    for (const auto &[orect, ocolor] : rects) {
                        if (&rect == &orect)
                            continue;
                        if (auto inter = rect.Intersection(orect)) {
                            auto copy = recent;
                            copy.push_back(&rect);
                            copy.push_back(&orect);
                            CalculateIntersections(*inter, color + ocolor, copy);
                        }
                    }
                }
                return;
            }
            SDL::Shapes::Rectangle shape(current);
            shape.SetColor(color);
            renderer.Draw(shape);
            for (const auto &[rect, col] : rects) {
                if (auto inter = rect.Intersection(current))
                    if (std::ranges::find(recent, &rect) == recent.end()) {
                        auto copy = recent;
                        copy.push_back(&rect);
                        CalculateIntersections(*inter, color + col, copy);
                    }
            }
        };

        CalculateIntersections(SDL::FRect(), SDL::Color::Transparent, {});

        if (((Now() - last) / 1000000).count() >= 1) {
            int number = static_cast<int>(1.0f / (static_cast<float>((Now() - last).count()) / 1000000));
            last = Now();
            int x = 1;
            for (int i = 0; i < std::log10(number); i++) {
                rects[4 - i].second = SDL::Color(number / x % 10 * 25, number / x % 10 * 25, number / x % 10 * 25);
                x *= 10;
            }
            window.SetTitle("Window! (" + std::to_string(number) + ")");
        }

        renderer.Display();
    }
    return 0;
}
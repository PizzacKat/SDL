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

struct PhysicalRectangle : SDL::Shapes::Rectangle {
    PhysicalRectangle()= default;

    PhysicalRectangle(const SDL::FRect rect, const SDL::Color color, float mass = 1): Rectangle(rect) {
        this->color = color;
        this->mass = mass;
    }

    void AddForce(const SDL::FVector2 vec) {
        acceleration = acceleration + vec / mass;
    }

    void Update(const float dt) {
        velocity = velocity + acceleration * dt;
        position = position + velocity * dt;
        velocity = velocity * std::pow(0.97f, dt);
        acceleration = {};
    }

    [[nodiscard]] SDL::FRect GetRect() const {
        return {position, size};
    }

    SDL::FVector2 velocity;
    SDL::FVector2 acceleration;
    float mass = 1;
};

int main() {
    SDL::Window window("Window!", {800, 600});
    SDL::Renderer renderer(window);
    SDL::FVector2 mouse;
    PhysicalRectangle rects[2] {
        PhysicalRectangle{{500, 500, 100, 100}, SDL::Color::Green, 10000}
    };

    float size = 5;
    int maxX = window.GetSize().x / static_cast<int>(size) - 1;
    for (int i = 1; i < std::size(rects); i++) {
        rects[i] = PhysicalRectangle(SDL::FRect{static_cast<float>(i % maxX) * size, static_cast<float>(i / maxX) * size, size, size}, SDL::Color::White);
    }

    PhysicalRectangle *grabbedRect = nullptr;
    SDL::FVector2 grabOffset;
    SDL::FVector2 lastMouse;

    std::chrono::microseconds last = Now();
    std::chrono::microseconds lastMouseTime = Now();
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
                    if (grabbedRect != nullptr) {
                        grabbedRect->position = mouse - grabOffset;
                        grabbedRect->velocity = (mouse - lastMouse) / (static_cast<float>((Now() - lastMouseTime).count()) / 1000000);
                        lastMouse = mouse;
                        lastMouseTime = Now();
                    }
                break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    for (auto &rect : rects)
                        if (rect.GetRect().Contains(mouse))
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
        deltaTime = static_cast<float>((Now() - last).count()) / 1000000;
        last = Now();
        renderer.Clear(SDL::Color::Black);

        for (auto &rect : rects) {
            if (grabbedRect != &rect) {
                rect.acceleration = rect.acceleration + SDL::FVector2(0, 9.81f);
                if (rect.position.y + rect.size.y > window.GetSize().y) {
                    rect.acceleration = {};
                    rect.velocity = rect.velocity * SDL::FVector2(1.0f, -1.0f);
                    rect.position.y = static_cast<float>(window.GetSize().y) - rect.size.y;
                }
                if (rect.position.y < 0) {
                    rect.acceleration = {};
                    rect.velocity = rect.velocity * SDL::FVector2(1.0f, -1.0f);
                    rect.position.y = 0;
                }
                if (rect.position.x + rect.size.x > window.GetSize().x) {
                    rect.acceleration = {};
                    rect.velocity = rect.velocity * SDL::FVector2(-1.0f, 1.0f);
                    rect.position.x = static_cast<float>(window.GetSize().x) - rect.size.x;
                }
                if (rect.position.x < 0) {
                    rect.acceleration = {};
                    rect.velocity = rect.velocity * SDL::FVector2(-1.0f, 1.0f);
                    rect.position.x = 0;
                }
                for (auto &other : rects) {
                    if (&rect == &other)
                        continue;
                    if (rect.GetRect().Intersects(other.GetRect())) {
                        const SDL::FVector2 center = rect.position + rect.size / 2;
                        const SDL::FVector2 size = other.size;
                        float distLeft = (center - other.position - SDL::FVector2(0.0f, size.y / 2.0f)).lengthSq();
                        float distRight = (center - other.position - SDL::FVector2(size.y, size.y / 2.0f)).lengthSq();
                        float distTop = (center - other.position - SDL::FVector2(size.x / 2.0f, 0.0f)).lengthSq();
                        float distBottom = (center - other.position - SDL::FVector2(size.x / 2.0f, size.y)).lengthSq();
                        float min = std::min({distLeft, distRight, distTop, distBottom});
                        if (min == distLeft || min == distRight) {
                            const float vel = rect.velocity.x;
                            const float oVel = other.velocity.x;
                            rect.velocity.x = (rect.mass - other.mass) / (rect.mass + other.mass) * vel + (other.mass * 2.0f) / (rect.mass + other.mass) * oVel;
                            other.velocity.x = (rect.mass * 2.0f) / (rect.mass + other.mass) * vel + (other.mass - rect.mass) / (rect.mass + other.mass) * oVel;
                            if (min == distLeft) {
                                const float x = (rect.position.x + rect.size.x + other.position.x) / 2.0f;
                                rect.position.x = x - rect.size.x;
                                other.position.x = x;
                            } else {
                                const float x = (rect.position.x + other.size.x + other.position.x) / 2.0f;
                                rect.position.x = x;
                                other.position.x = x - other.size.x;
                            }
                        }
                        if (min == distTop || min == distBottom) {
                            const float vel = rect.velocity.y;
                            const float oVel = other.velocity.y;
                            rect.velocity.y = (rect.mass - other.mass) / (rect.mass + other.mass) * vel + (other.mass * 2.0f) / (rect.mass + other.mass) * oVel;
                            other.velocity.y = (rect.mass * 2.0f) / (rect.mass + other.mass) * vel + (other.mass - rect.mass) / (rect.mass + other.mass) * oVel;
                            if (min == distTop) {
                                const float y = (rect.position.y + rect.size.y + other.position.y) / 2.0f;
                                rect.position.y = y - rect.size.y;
                                other.position.y = y;
                            } else {
                                const float y = (rect.position.y + other.size.y + other.position.y) / 2.0f;
                                rect.position.y = y;
                                other.position.y = y - other.size.y;
                            }
                        }
                    }
                }
            }
        }

        for (auto &rect : rects) {
            if (grabbedRect != &rect)
                rect.Update(0.01f);
            renderer.Draw(rect);
        }

        std::function<void(SDL::FRect, SDL::Color, std::vector<const PhysicalRectangle *>)> CalculateIntersections = [&CalculateIntersections, &rects, &renderer](const SDL::FRect current, const SDL::Color color, std::vector<const PhysicalRectangle *> recent) {
            if (current == SDL::FRect()) {
                for (const auto &rect : rects) {
                    for (const auto &orect : rects) {
                        if (&rect == &orect)
                            continue;
                        if (auto inter = rect.GetRect().Intersection(orect.GetRect())) {
                            auto copy = recent;
                            copy.push_back(&rect);
                            copy.push_back(&orect);
                            CalculateIntersections(*inter, rect.color + orect.color, copy);
                        }
                    }
                }
                return;
            }
            SDL::Shapes::Rectangle shape(current);
            shape.color = color;
            renderer.Draw(shape);
            for (const auto &rect : rects) {
                if (auto inter = rect.GetRect().Intersection(current))
                    if (std::ranges::find(recent, &rect) == recent.end()) {
                        auto copy = recent;
                        copy.push_back(&rect);
                        CalculateIntersections(*inter, color + rect.color, copy);
                    }
            }
        };

        CalculateIntersections(SDL::FRect(), SDL::Color::Transparent, {});

        int number = static_cast<int>(1.0f / deltaTime);
        window.SetTitle("Window! (" + std::to_string(number) + ")");

        renderer.Display();
    }
    return 0;
}
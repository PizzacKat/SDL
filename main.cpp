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

class Transform3D {
public:
    Transform3D() {

    }

    Transform3D(const SDL::FMatrix4x4 &matrix): _transform(matrix) {

    }

    Transform3D &Translate(const SDL::FVector3 &delta) {
        const SDL::FMatrix4x4 matrix(
            1, 0, 0, delta.x,
            0, 1, 0, delta.y,
            0, 0, 1, delta.z,
            0, 0, 0,       1
        );

        return *this *= matrix;
    }

    Transform3D &Rotate(const SDL::FVector3 &euler) {
        const SDL::FMatrix4x4 matrixZ(
            std::cos(euler.x), -std::sin(euler.x), 0, 0,
            std::sin(euler.x),  std::cos(euler.x), 0, 0,
                            0,                  0, 1, 0,
                            0,                  0, 0, 1
        );
        const SDL::FMatrix4x4 matrixY(
             std::cos(euler.y), 0, std::sin(euler.y), 0,
                             0, 1,                 0, 0,
            -std::sin(euler.y), 0, std::cos(euler.y), 0,
                             0, 0,                 0, 1
        );
        const SDL::FMatrix4x4 matrixX(
            1,                 0,                  0, 0,
            0, std::cos(euler.z), -std::sin(euler.z), 0,
            0, std::sin(euler.z),  std::cos(euler.z), 0,
            0,                 0,                  0, 1
        );

        return *this *= matrixZ * matrixY * matrixX;
    }

    Transform3D &Scale(const SDL::FVector3 &scale) {
        const SDL::FMatrix4x4 matrix(
            scale.x,       0,       0, 0,
                  0, scale.y,       0, 0,
                  0,       0, scale.z, 0,
                  0,       0,       0, 1
        );

        return *this *= matrix;
    }

    Transform3D &operator*=(const Transform3D &other) {
        _transform *= other._transform;
        return *this;
    }

    [[nodiscard]] SDL::FVector3 Apply(const SDL::FVector3 &vec3) const {
        return SDL::FVector3(_transform * SDL::FMatrix4x4(vec3));
    }

    [[nodiscard]] SDL::FVector4 Apply(const SDL::FVector4 &vec4) const {
        return SDL::FVector4(_transform * SDL::FMatrix4x4(vec4));
    }

    [[nodiscard]] const SDL::FMatrix4x4 &GetMatrix() const {
        return _transform;
    }
private:
    SDL::FMatrix4x4 _transform = SDL::FMatrix4x4::Identity;
};

class View3D {
public:
    View3D(): View3D(0.001, 1000, 90) {

    }

    View3D(const float minClip, const float maxClip, const float fov): _minClip(minClip), _maxClip(maxClip), _fov(fov) {

    }

    void SetNearClip(const float minClip) {
        _minClip = minClip;
    }

    [[nodiscard]] float GetNearClip() const {
        return _minClip;
    }

    void SetFarClip(const float maxClip) {
        _maxClip = maxClip;
    }

    [[nodiscard]] float GetFarClip() const {
        return _maxClip;
    }

    void SetFOV(const float fov) {
        _fov = fov;
    }

    [[nodiscard]] float GetFOV() const {
        return _fov;
    }

    [[nodiscard]] SDL::FMatrix4x4 GetMatrix() const {
        const float S = 1 / std::tan(_fov / 2 * std::numbers::pi_v<float> / 180.0f);
        const float f = _maxClip, n = _minClip;
        return {
            S, 0,             0,  0,
            0, S,             0,  0,
            0, 0, -(   f/(f-n)), -1,
            0, 0,  (-f*n/(f-n)),  0
        };
    }

private:
    float _minClip;
    float _maxClip;
    float _fov;
};

int main() {
    SDL::Window window("Window!", {900, 900}, SDL_WINDOW_TRANSPARENT | SDL_WINDOW_RESIZABLE);
    SDL::Renderer renderer(window);
    SDL::FVector2 mouse;
    SDL::FramerateLimiter limiter(1000);

    SDL::Timer timer;
    float deltaTime = 0.0f;
    float time = 0.0f;

    const SDL::FVector3 points[8] = {
        {0, 0, 0}, {1, 0, 0}, {1, 0, 1},
        {0, 1, 0}, {1, 1, 0}, {1, 1, 1},
        {0, 1, 1}, {0, 0, 1}
    };

    SDL::VertexBuffer buffer;

    std::array<int, 4> faces[] = {
        {0, 1, 3, 4},
        {1, 2, 0, 7},
        {0, 7, 3, 6},
        {7, 2, 6, 5},
        {1, 2, 4, 5},
        {3, 4, 6, 5}
    };

    float distances[8] {};

    SDL::Color color[8] {
        SDL::Color::Blue,
        SDL::Color::Green,
        SDL::Color::Red,
        SDL::Color::Yellow,
        SDL::Color::White,
        SDL::Color::Blue,
        SDL::Color::Green,
        SDL::Color::White
    };

    while (running) {
        View3D view;
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
        renderer.Clear(SDL::Color::Transparent);

        time += deltaTime;

        buffer.ClearVertices();

        Transform3D transform;
        transform *= view.GetMatrix();

        transform.Translate({0, 0, -6});
        transform.Rotate({0, time, 0});
        transform.Scale({1, 1, 1});
        transform.Translate({-0.5, -0.5, -0.5});

        for (std::size_t i = 0; i < 8; ++i) {
            SDL::FVector4 vec4(points[i], 1.0f);
            vec4 = transform.Apply(vec4);
            distances[i] = vec4.z;
            vec4.x /= vec4.w;
            vec4.y /= vec4.w;
            vec4.z /= vec4.w;
            buffer.Add(SDL::Vertex(SDL::FVector2(SDL::FVector3(vec4)) + window.GetSize() / 2.0f, color[i]));
        }

        std::pair<float, std::array<int, 4>> fack[6];

        for (std::size_t i = 0; i < 6; ++i) {
            float avgDist = (distances[faces[i][0]] + distances[faces[i][1]] + distances[faces[i][2]] + distances[faces[i][3]]);
            fack[i] = std::make_pair(avgDist, faces[i]);
        }

        std::ranges::sort(fack, [](const auto &a, const auto &b) { return a.first > b.first; });

        buffer.ClearIndices();

        for (const auto &[_, values] : fack) {
            buffer.Add(values[0]);
            buffer.Add(values[2]);
            buffer.Add(values[1]);
            buffer.Add(values[1]);
            buffer.Add(values[2]);
            buffer.Add(values[3]);
        }

        renderer.Draw(buffer);

        renderer.Display();
        SDL::FramerateType framerate = limiter.Update();
        window.SetTitle(std::to_string(framerate));
    }
    return 0;
}
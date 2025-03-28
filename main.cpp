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
#include <array>
#include <SDL3/SDL_hints.h>

#include "SDL/Surface.hpp"

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

    Transform3D &Rotate(SDL::FVector3 euler) {
        euler *= std::numbers::pi_v<float> / 180.0f;
        const SDL::FMatrix4x4 matrixZ(
            std::cos(euler.z), -std::sin(euler.z), 0, 0,
            std::sin(euler.z),  std::cos(euler.z), 0, 0,
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
            0, std::cos(euler.x), -std::sin(euler.x), 0,
            0, std::sin(euler.x),  std::cos(euler.x), 0,
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

void RenderFace(SDL::Renderer &renderer,
    const SDL::FVector2 p1,
    const SDL::FVector2 p2,
    const SDL::FVector2 p3,
    const SDL::FVector2 p4,
    const SDL::Color &color,
    const SDL::FVector2 uv1 = {},
    const SDL::FVector2 uv2 = {},
    const SDL::FVector2 uv3 = {},
    const SDL::FVector2 uv4 = {}, const SDL::Texture &texture = nullptr) {
    const SDL_Vertex vertices[4] = {
        SDL::Vertex{p1, color, uv1},
        SDL::Vertex{p2, color, uv2},
        SDL::Vertex{p3, color, uv3},
        SDL::Vertex{p4, color, uv4}
    };
    const int indices[6] = {
        0, 2, 1, 1, 2, 3
    };

    renderer.Draw(vertices, 4, indices, 6, texture);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const SDL::Vector2<T> &position) {
    os << "(" << position.x << ", " << position.y << ")";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const SDL::Vector3<T> &position) {
    os << "(" << position.x << ", " << position.y << ", " << position.z << ")";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const SDL::Vector4<T> &position) {
    os << "(" << position.x << ", " << position.y << ", " << position.z << ", " << position.w << ")";
    return os;
}

int main() {
    SDL::Window window("Window!", {260, 260}, SDL_WINDOW_TRANSPARENT | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_UTILITY);
    SDL::Renderer renderer(window);
    SDL::FVector2 mouse;
    SDL::FramerateLimiter limiter(240);
    SDL::Texture faceTexture;
    faceTexture.LoadFile(renderer, "texture.png");

    SDL::Timer timer;
    float deltaTime = 0.0f;
    float time = 0.0f;

    const SDL::FVector3 points[8] = {
        {0, 0, 0}, {1, 0, 0}, {1, 0, 1},
        {0, 1, 0}, {1, 1, 0}, {1, 1, 1},
        {0, 1, 1}, {0, 0, 1}
    };

    const std::array<std::pair<int, SDL::FVector2>, 4> faces[6] = {
        {
            std::pair{0, SDL::FVector2{1.0 / 4, 2.0 / 3}},
            std::pair{1, SDL::FVector2{2.0 / 4, 2.0 / 3}},
            std::pair{3, SDL::FVector2{1.0 / 4, 1.0 / 3}},
            std::pair{4, SDL::FVector2{2.0 / 4, 1.0 / 3}}
        },
        {
            std::pair{1, SDL::FVector2{2.0 / 4, 0.0 / 3}},
            std::pair{2, SDL::FVector2{2.0 / 4, 1.0 / 3}},
            std::pair{0, SDL::FVector2{1.0 / 4, 0.0 / 3}},
            std::pair{7, SDL::FVector2{1.0 / 4, 1.0 / 3}}
        },
        {
            std::pair{0, SDL::FVector2{1.0 / 4, 2.0 / 3}},
            std::pair{7, SDL::FVector2{0.0 / 4, 2.0 / 3}},
            std::pair{3, SDL::FVector2{1.0 / 4, 1.0 / 3}},
            std::pair{6, SDL::FVector2{0.0 / 4, 1.0 / 3}}
        },
        {
            std::pair{2, SDL::FVector2{3.0 / 4, 2.0 / 3}},
            std::pair{7, SDL::FVector2{4.0 / 4, 2.0 / 3}},
            std::pair{5, SDL::FVector2{3.0 / 4, 1.0 / 3}},
            std::pair{6, SDL::FVector2{4.0 / 4, 1.0 / 3}}
        },
        {
            std::pair{1, SDL::FVector2{2.0 / 4, 2.0 / 3}},
            std::pair{2, SDL::FVector2{3.0 / 4, 2.0 / 3}},
            std::pair{4, SDL::FVector2{2.0 / 4, 1.0 / 3}},
            std::pair{5, SDL::FVector2{3.0 / 4, 1.0 / 3}}
        },
        {
            std::pair{3, SDL::FVector2{1.0 / 4, 3.0 / 3}},
            std::pair{4, SDL::FVector2{2.0 / 4, 3.0 / 3}},
            std::pair{6, SDL::FVector2{1.0 / 4, 2.0 / 3}},
            std::pair{5, SDL::FVector2{2.0 / 4, 2.0 / 3}}
        },
    };

    bool mouseDown = false;
    bool cameraDown = false;

    SDL::FVector2 grabPos;
    SDL::FVector3 cameraRot{-15, 0, 0};

    float cameraSens = 0.5f;

    while (running) {
        View3D view;
        while (const std::optional<SDL::Event> event = SDL::PollEvent()) {
            switch (event->type) {
                case SDL_EVENT_QUIT:
                    running = false;
                break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    SDL_GetGlobalMouseState(&grabPos.x, &grabPos.y);
                if (event->button.button == SDL_BUTTON_LEFT) {
                    mouseDown = true;
                    grabPos -= window.GetPosition();
                } else if (event->button.button == SDL_BUTTON_RIGHT)
                    cameraDown = true;
                break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    if (event->button.button == SDL_BUTTON_LEFT)
                        mouseDown = false;
                    else if (event->button.button == SDL_BUTTON_RIGHT)
                        cameraDown = false;
                break;
                default:
                break;
            }
        }
        deltaTime = timer.Restart().AsSeconds();

        if (mouseDown) {
            SDL_GetGlobalMouseState(&mouse.x, &mouse.y);
            window.SetPosition(mouse - grabPos);
        }

        if (cameraDown) {
            SDL_GetGlobalMouseState(&mouse.x, &mouse.y);
            cameraRot += SDL::FVector2(-(mouse.y - grabPos.y), mouse.x - grabPos.x) * cameraSens;
            grabPos = mouse;
        }

        renderer.Clear(SDL::Color::Transparent);

        time += deltaTime;

        Transform3D transform;
        transform *= view.GetMatrix();

        transform.Translate({0, 0, 6});
        transform.Rotate({cameraRot.x, 0, 0});
        transform.Rotate({0, cameraRot.y, 0});
        transform.Rotate({0, time * 60, 0});
        transform.Scale({1, 1, -1});
        transform.Translate({-0.5, -0.5, -0.5});

        SDL::FVector3 viewPoints[8];

        for (std::size_t i = 0; i < 8; ++i) {
            SDL::FVector4 vec4(points[i], 1.0f);
            vec4 = transform.Apply(vec4);
            vec4.x /= vec4.w;
            vec4.y /= vec4.w;
            vec4.z /= vec4.w;
            viewPoints[i] = SDL::FVector3(SDL::FVector3(vec4) + SDL::FVector3(window.GetSize()) / 2.0f);
        }

        std::array<std::pair<SDL::FVector3, SDL::FVector2>, 4> vertexFaces[6];

        for (std::size_t j = 0; j < 4; ++j) {
            for (std::size_t i = 0; i < 6; ++i) {
                vertexFaces[i][j] = {viewPoints[faces[i][j].first], faces[i][j].second};
            }
        }

        std::ranges::sort(vertexFaces, [](const auto &a, const auto &b) {
            float dA = (a[0].first + a[1].first + a[2].first + a[3].first).z;
            float dB = (b[0].first + b[1].first + b[2].first + b[3].first).z;
            return dB > dA;
        });

        renderer.SetDrawColor(SDL::Color::Black);
        for (const auto &vertices : vertexFaces) {
            const auto p1 = vertices[0].first;
            const auto p2 = vertices[1].first;
            const auto p3 = vertices[2].first;
            const auto p4 = vertices[3].first;
            RenderFace(renderer, SDL::FVector2(p1), SDL::FVector2(p2), SDL::FVector2(p3), SDL::FVector2(p4), SDL::Color::White, vertices[0].second, vertices[1].second, vertices[2].second, vertices[3].second, faceTexture);
        }
        renderer.Display();
        SDL::FramerateType framerate = limiter.Update();
        window.SetTitle(std::to_string(framerate));
    }
    return 0;
}
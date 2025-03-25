#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include "Shape.hpp"
#include "Transform.hpp"

namespace SDL {
    class Transformable : public Shape {
    public:
        Transformable();

        void SetPosition(const FVector2 &position);
        [[nodiscard]] const FVector2 &GetPosition() const;
        void SetScale(const FVector2 &scale);
        [[nodiscard]] const FVector2 &GetScale() const;
        void SetRotation(float rotation);
        [[nodiscard]] float GetRotation() const;
        void SetOrigin(const FVector2 &origin);
        [[nodiscard]] const FVector2 &GetOrigin() const;

        [[nodiscard]] const SDL::Transform &GetTransform() const;

    protected:
        void RecomputeTransform();

        void Transform(FVector2 &v) const override;
    private:
        FVector2 _position, _scale{1.0f, 1.0f}, _origin;
        float _rotation = 0.0f;
        SDL::Transform _transform;
    };
}

#endif //TRANSFORMABLE_HPP

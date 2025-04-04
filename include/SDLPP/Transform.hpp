#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Angle.hpp"
#include "Matrix.hpp"

namespace SDL {
    class Transform {
    public:
        Transform();
        Transform(const FMatrix3x3 &matrix);

        Transform &Translate(const FVector2 &delta);
        Transform &Rotate(const Angle &angle);
        Transform &Scale(const FVector2 &scale);

        Transform operator*(const Transform &other) const;
        Transform &operator*=(const Transform &other);

        [[nodiscard]] FVector2 Apply(const FVector2 &point) const;
        [[nodiscard]] FVector3 Apply(const FVector3 &point) const;

        [[nodiscard]] Transform Inverse() const;

        [[nodiscard]] const FMatrix3x3 &GetMatrix() const;
    private:
        FMatrix3x3 _transform = FMatrix3x3::Identity;
    };
}

#endif //TRANSFORM_HPP

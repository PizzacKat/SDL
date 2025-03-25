#include "SDL/Transform.hpp"

namespace SDL {
    Transform::Transform() {

    }

    Transform::Transform(const FMatrix3x3 &matrix): _transform(matrix) {

    }

    Transform &Transform::Translate(const FVector2 &delta) {
        const FMatrix3x3 matrix(
            1, 0, delta.x,
            0, 1, delta.y,
            0, 0,        1
        );

        return *this *= matrix;
    }

    Transform &Transform::Rotate(const float angle) {
        const FMatrix3x3 matrix(
            std::cos(angle), -std::sin(angle), 0,
            std::sin(angle),  std::cos(angle), 0,
                          0,                0, 1
        );

        return *this *= matrix;
    }

    Transform &Transform::Scale(const FVector2 &scale) {
        const FMatrix3x3 matrix(
            scale.x,       0, 0,
                  0, scale.y, 0,
                  0,       0, 1
        );

        return *this *= matrix;
    }

    Transform Transform::operator*(const Transform &other) const {
        return {_transform * other._transform};
    }

    Transform &Transform::operator*=(const Transform &other) {
        _transform *= other._transform;
        return *this;
    }

    FVector2 Transform::Apply(const FVector2 &point) const {
        return static_cast<FVector2>(_transform * FMatrix3x3(point));
    }

    FVector3 Transform::Apply(const FVector3 &point) const {
        return static_cast<FVector3>(_transform * FMatrix3x3(point));
    }

    Transform Transform::Inverse() const {
        const float *m = _transform.Data();
        const float det = m[0]*m[4]*m[8] + m[1]*m[5]*m[6] + m[2]*m[3]*m[7];
        if (det == 0)
            return FMatrix3x3::Identity;
        return FMatrix3x3(
             (m[4]*m[8] - m[5]*m[7]) / det, -(m[1]*m[8] - m[2]*m[7]) / det,  (m[1]*m[5] - m[2]*m[4]) / det,
            -(m[3]*m[8] - m[5]*m[6]) / det,  (m[0]*m[8] - m[2]*m[6]) / det, -(m[0]*m[5] - m[2]*m[3]) / det,
             (m[3]*m[7] - m[4]*m[6]) / det, -(m[0]*m[7] - m[1]*m[6]) / det,  (m[0]*m[4] - m[1]*m[3]) / det
        );
    }

    const FMatrix3x3 &Transform::GetMatrix() const {
        return _transform;
    }
}
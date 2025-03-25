#include "SDL/Transformable.hpp"

namespace SDL {
    Transformable::Transformable()= default;

    void Transformable::SetPosition(const FVector2 &position) {
        _position = position;
        RecomputeTransform();
    }

    const FVector2 &Transformable::GetPosition() const {
        return _position;
    }

    void Transformable::SetScale(const FVector2 &scale) {
        _scale = scale;
        RecomputeTransform();
    }

    const FVector2 &Transformable::GetScale() const {
        return _scale;
    }

    void Transformable::SetRotation(const float rotation) {
        _rotation = rotation;
        RecomputeTransform();
    }

    float Transformable::GetRotation() const {
        return _rotation;
    }

    void Transformable::SetOrigin(const FVector2 &origin) {
        _origin = origin;
        RecomputeTransform();
    }

    const FVector2 &Transformable::GetOrigin() const {
        return _origin;
    }

    const Transform &Transformable::GetTransform() const {
        return _transform;
    }

    void Transformable::Transform(FVector2 &v) const {
        v = _transform.Apply(v);
    }

    void Transformable::RecomputeTransform() {
        SDL::Transform transform;
        transform.Translate(_position);
        transform.Rotate(_rotation);
        transform.Scale(_scale);
        transform.Translate(-_origin);
        _transform = transform;
        Recompute();
    }


}
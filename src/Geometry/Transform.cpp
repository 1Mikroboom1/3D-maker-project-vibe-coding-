#include "Transform.h"
#include <ostream>

namespace VisionBIM::Geometry
{

Transform::Transform(const Vector3& pos)
    : position(pos), scale(1.0)
{
}

Transform::Transform(const Vector3& pos, const Vector3& scl)
    : position(pos), scale(scl)
{
}

Matrix4 Transform::GetMatrix() const
{
    Matrix4 scaleMat = Matrix4::Scaling(scale);
    Matrix4 transMat = Matrix4::Translation(position);
    return transMat * scaleMat;
}

Matrix4 Transform::GetInverseMatrix() const
{
    Vector3 invScale(
        std::abs(scale.x) > MathConstants::Epsilon ? 1.0 / scale.x : 0.0,
        std::abs(scale.y) > MathConstants::Epsilon ? 1.0 / scale.y : 0.0,
        std::abs(scale.z) > MathConstants::Epsilon ? 1.0 / scale.z : 0.0
    );

    Vector3 invPosition(-position.x, -position.y, -position.z);

    Matrix4 inv = Matrix4::Scaling(invScale);
    inv = inv * Matrix4::Translation(invPosition);

    return inv;
}

Vector3 Transform::TransformPoint(const Vector3& point) const
{
    return GetMatrix().TransformPoint(point);
}

Vector3 Transform::TransformVector(const Vector3& vec) const
{
    return GetMatrix().TransformVector(vec);
}

Vector3 Transform::TransformDirection(const Vector3& dir) const
{
    return GetMatrix().TransformDirection(dir);
}

Vector3 Transform::InverseTransformPoint(const Vector3& point) const
{
    return GetInverseMatrix().TransformPoint(point);
}

Vector3 Transform::InverseTransformVector(const Vector3& vec) const
{
    return GetInverseMatrix().TransformVector(vec);
}

void Transform::Translate(const Vector3& delta)
{
    position += delta;
}

void Transform::SetScale(const Vector3& newScale)
{
    scale = newScale;
}

bool Transform::operator==(const Transform& other) const
{
    return position == other.position && scale == other.scale;
}

bool Transform::operator!=(const Transform& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Transform& t)
{
    return os << "Transform(pos: " << t.position 
              << ", scale: " << t.scale << ")";
}

} // namespace VisionBIM::Geometry
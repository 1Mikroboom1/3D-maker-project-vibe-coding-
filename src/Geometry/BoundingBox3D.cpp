#include "BoundingBox3D.h"
#include <algorithm>
#include <vector>

namespace VisionBIM::Geometry
{

BoundingBox3D::BoundingBox3D()
    : min(MathConstants::MaxDouble, MathConstants::MaxDouble, MathConstants::MaxDouble)
    , max(MathConstants::MinDouble, MathConstants::MinDouble, MathConstants::MinDouble)
{
}

BoundingBox3D::BoundingBox3D(const Vector3& min, const Vector3& max)
    : min(min), max(max)
{
}

void BoundingBox3D::Reset()
{
    min = Vector3(MathConstants::MaxDouble);
    max = Vector3(MathConstants::MinDouble);
}

void BoundingBox3D::Expand(const Vector3& point)
{
    min.x = std::min(min.x, point.x);
    min.y = std::min(min.y, point.y);
    min.z = std::min(min.z, point.z);

    max.x = std::max(max.x, point.x);
    max.y = std::max(max.y, point.y);
    max.z = std::max(max.z, point.z);
}

void BoundingBox3D::Expand(const BoundingBox3D& other)
{
    if (!other.IsValid()) return;
    Expand(other.min);
    Expand(other.max);
}

BoundingBox3D BoundingBox3D::FromPoints(const Vector3* points, size_t count)
{
    BoundingBox3D box;
    for (size_t i = 0; i < count; ++i)
        box.Expand(points[i]);
    return box;
}

BoundingBox3D BoundingBox3D::FromPoints(const std::vector<Vector3>& points)
{
    return FromPoints(points.data(), points.size());
}

Vector3 BoundingBox3D::Center() const
{
    return (min + max) * 0.5;
}

Vector3 BoundingBox3D::Size() const
{
    return max - min;
}

Vector3 BoundingBox3D::Extents() const
{
    return Size() * 0.5;
}

double BoundingBox3D::Volume() const
{
    Vector3 s = Size();
    return s.x * s.y * s.z;
}

bool BoundingBox3D::IsValid() const
{
    return min.x <= max.x && min.y <= max.y && min.z <= max.z;
}

bool BoundingBox3D::IsEmpty() const
{
    return !IsValid() || Volume() < MathConstants::Epsilon;
}

bool BoundingBox3D::Contains(const Vector3& point) const
{
    return point.x >= min.x && point.x <= max.x &&
           point.y >= min.y && point.y <= max.y &&
           point.z >= min.z && point.z <= max.z;
}

bool BoundingBox3D::Contains(const BoundingBox3D& other) const
{
    return Contains(other.min) && Contains(other.max);
}

bool BoundingBox3D::Intersects(const BoundingBox3D& other) const
{
    return !(max.x < other.min.x || min.x > other.max.x ||
             max.y < other.min.y || min.y > other.max.y ||
             max.z < other.min.z || min.z > other.max.z);
}

Vector3 BoundingBox3D::ClosestPoint(const Vector3& point) const
{
    return Vector3(
        Math::Clamp(point.x, min.x, max.x),
        Math::Clamp(point.y, min.y, max.y),
        Math::Clamp(point.z, min.z, max.z)
    );
}

bool BoundingBox3D::operator==(const BoundingBox3D& other) const
{
    return min == other.min && max == other.max;
}

bool BoundingBox3D::operator!=(const BoundingBox3D& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const BoundingBox3D& box)
{
    return os << "BoundingBox3D(min: " << box.min 
              << ", max: " << box.max << ")";
}

} // namespace VisionBIM::Geometry
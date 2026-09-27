#include "BoundingBox2D.h"
#include <algorithm>
#include <limits>
#include <vector>

namespace VisionBIM::Geometry
{

BoundingBox2D::BoundingBox2D()
    : min(MathConstants::MaxDouble, MathConstants::MaxDouble)
    , max(MathConstants::MinDouble, MathConstants::MinDouble)
{
}

BoundingBox2D::BoundingBox2D(const Vector2& min, const Vector2& max)
    : min(min), max(max)
{
}

void BoundingBox2D::Reset()
{
    min = Vector2(MathConstants::MaxDouble);
    max = Vector2(MathConstants::MinDouble);
}

void BoundingBox2D::Expand(const Vector2& point)
{
    min.x = std::min(min.x, point.x);
    min.y = std::min(min.y, point.y);
    max.x = std::max(max.x, point.x);
    max.y = std::max(max.y, point.y);
}

void BoundingBox2D::Expand(const BoundingBox2D& other)
{
    if (!other.IsValid()) return;
    Expand(other.min);
    Expand(other.max);
}

BoundingBox2D BoundingBox2D::FromPoints(const Vector2* points, size_t count)
{
    BoundingBox2D box;
    for (size_t i = 0; i < count; ++i)
        box.Expand(points[i]);
    return box;
}

BoundingBox2D BoundingBox2D::FromPoints(const std::vector<Vector2>& points)
{
    return FromPoints(points.data(), points.size());
}

Vector2 BoundingBox2D::Center() const
{
    return (min + max) * 0.5;
}

Vector2 BoundingBox2D::Size() const
{
    return max - min;
}

Vector2 BoundingBox2D::Extents() const
{
    return Size() * 0.5;
}

double BoundingBox2D::Area() const
{
    Vector2 s = Size();
    return s.x * s.y;
}

bool BoundingBox2D::IsValid() const
{
    return min.x <= max.x && min.y <= max.y;
}

bool BoundingBox2D::IsEmpty() const
{
    return !IsValid() || Area() < MathConstants::Epsilon;
}

bool BoundingBox2D::Contains(const Vector2& point) const
{
    return point.x >= min.x && point.x <= max.x &&
           point.y >= min.y && point.y <= max.y;
}

bool BoundingBox2D::Contains(const BoundingBox2D& other) const
{
    return Contains(other.min) && Contains(other.max);
}

bool BoundingBox2D::Intersects(const BoundingBox2D& other) const
{
    return !(max.x < other.min.x || min.x > other.max.x ||
             max.y < other.min.y || min.y > other.max.y);
}

Vector2 BoundingBox2D::ClosestPoint(const Vector2& point) const
{
    return Vector2(
        Math::Clamp(point.x, min.x, max.x),
        Math::Clamp(point.y, min.y, max.y)
    );
}

bool BoundingBox2D::operator==(const BoundingBox2D& other) const
{
    return min == other.min && max == other.max;
}

bool BoundingBox2D::operator!=(const BoundingBox2D& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const BoundingBox2D& box)
{
    return os << "BoundingBox2D(min: " << box.min 
              << ", max: " << box.max << ")";
}

} // namespace VisionBIM::Geometry
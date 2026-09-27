#include "Line2D.h"
#include <cmath>

namespace VisionBIM::Geometry
{

Line2D::Line2D() : point(0.0, 0.0), direction(1.0, 0.0) {}

Line2D::Line2D(const Vector2& p, const Vector2& dir)
    : point(p), direction(dir)
{
}

Line2D Line2D::FromTwoPoints(const Vector2& a, const Vector2& b)
{
    return Line2D(a, b - a);
}

Vector2 Line2D::ProjectPoint(const Vector2& p) const
{
    Vector2 ap = p - point;
    double t = ap.Dot(direction) / direction.LengthSquared();
    return point + direction * t;
}

double Line2D::Distance(const Vector2& p) const
{
    Vector2 projection = ProjectPoint(p);
    return (p - projection).Length();
}

double Line2D::Angle(const Line2D& other) const
{
    double dot = direction.Dot(other.direction);
    double len1 = direction.Length();
    double len2 = other.direction.Length();

    if (len1 < MathConstants::Epsilon || len2 < MathConstants::Epsilon)
        return 0.0;

    double cosTheta = Math::Clamp(dot / (len1 * len2), -1.0, 1.0);
    return std::acos(cosTheta);
}

double Line2D::AngleDegrees(const Line2D& other) const
{
    return Math::RadiansToDegrees(Angle(other));
}

bool Line2D::IsParallel(const Line2D& other) const
{
    double cross = direction.x * other.direction.y - direction.y * other.direction.x;
    return std::abs(cross) < MathConstants::Epsilon;
}

bool Line2D::IsCoincident(const Line2D& other) const
{
    if (!IsParallel(other))
        return false;

    Vector2 diff = other.point - point;
    double cross = diff.x * direction.y - diff.y * direction.x;
    return std::abs(cross) < MathConstants::Epsilon;
}

void Line2D::NormalizeDirection()
{
    direction.Normalize();
}

Line2D Line2D::Normalized() const
{
    Line2D result = *this;
    result.NormalizeDirection();
    return result;
}

} // namespace VisionBIM::Geometry
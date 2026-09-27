#include "Segment2D.h"
#include <algorithm>

namespace VisionBIM::Geometry
{

Segment2D::Segment2D() : a(0.0, 0.0), b(1.0, 0.0) {}

Segment2D::Segment2D(const Vector2& a, const Vector2& b)
    : a(a), b(b)
{
}

Vector2 Segment2D::Midpoint() const
{
    return (a + b) * 0.5;
}

double Segment2D::Length() const
{
    return (b - a).Length();
}

double Segment2D::LengthSquared() const
{
    return (b - a).LengthSquared();
}

Line2D Segment2D::ToLine() const
{
    return Line2D::FromTwoPoints(a, b);
}

Vector2 Segment2D::ProjectPoint(const Vector2& p) const
{
    Vector2 ab = b - a;
    Vector2 ap = p - a;
    double lenSq = ab.LengthSquared();

    if (lenSq < MathConstants::Epsilon)
        return a; // вырожденный отрезок

    double t = Math::Clamp(ap.Dot(ab) / lenSq, 0.0, 1.0);
    return a + ab * t;
}

double Segment2D::Distance(const Vector2& p) const
{
    Vector2 projection = ProjectPoint(p);
    return (p - projection).Length();
}

bool Segment2D::Contains(const Vector2& p, double epsilon) const
{
    return Distance(p) <= epsilon;
}

bool Segment2D::Intersects(const Segment2D& other, Vector2* intersectionPoint) const
{
    Vector2 a1 = a;
    Vector2 b1 = b;
    Vector2 a2 = other.a;
    Vector2 b2 = other.b;

    Vector2 d1 = b1 - a1;
    Vector2 d2 = b2 - a2;

    double denom = d1.x * d2.y - d1.y * d2.x;

    if (std::abs(denom) < MathConstants::Epsilon)
        return false; // параллельны

    double t = ((a2.x - a1.x) * d2.y - (a2.y - a1.y) * d2.x) / denom;
    double s = ((a2.x - a1.x) * d1.y - (a2.y - a1.y) * d1.x) / denom;

    bool intersects = (t >= 0.0 && t <= 1.0) && (s >= 0.0 && s <= 1.0);

    if (intersects && intersectionPoint)
    {
        *intersectionPoint = a1 + d1 * t;
    }

    return intersects;
}

} // namespace VisionBIM::Geometry
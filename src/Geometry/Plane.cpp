#include "Plane.h"
#include "Ray.h"
#include <ostream>
#include <cmath>

namespace VisionBIM::Geometry
{

Plane::Plane() 
    : normal(0.0, 0.0, 1.0), distance(0.0)
{
}

Plane::Plane(const Vector3& n, double d)
    : normal(n), distance(d)
{
}

Plane::Plane(const Vector3& normal, const Vector3& pointOnPlane)
    : normal(normal), distance(normal.Dot(pointOnPlane))
{
}

Plane Plane::FromThreePoints(const Vector3& a, const Vector3& b, const Vector3& c)
{
    Vector3 ab = b - a;
    Vector3 ac = c - a;
    Vector3 n = ab.Cross(ac);

    if (n.LengthSquared() < MathConstants::Epsilon)
        return Plane(); // вырожденная плоскость

    n.Normalize();
    return Plane(n, a);
}

void Plane::Normalize()
{
    double len = normal.Length();
    if (len > MathConstants::Epsilon)
    {
        normal /= len;
        distance /= len;
    }
}

Plane Plane::Normalized() const
{
    Plane result = *this;
    result.Normalize();
    return result;
}

double Plane::SignedDistance(const Vector3& point) const
{
    return normal.Dot(point) - distance;
}

double Plane::Distance(const Vector3& point) const
{
    return std::abs(SignedDistance(point));
}

Vector3 Plane::ProjectPoint(const Vector3& point) const
{
    double dist = SignedDistance(point);
    return point - normal * dist;
}

bool Plane::IntersectRay(const Ray& ray, double& outT) const
{
    double denom = normal.Dot(ray.direction);

    if (std::abs(denom) < MathConstants::Epsilon)
        return false; // параллельно

    outT = (distance - normal.Dot(ray.origin)) / denom;

    return outT >= 0.0;
}

bool Plane::IsPointOnPlane(const Vector3& point, double epsilon) const
{
    return std::abs(SignedDistance(point)) <= epsilon;
}

bool Plane::operator==(const Plane& other) const
{
    return normal == other.normal && 
           Math::NearlyEqual(distance, other.distance);
}

bool Plane::operator!=(const Plane& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Plane& plane)
{
    return os << "Plane(normal: " << plane.normal 
              << ", distance: " << plane.distance << ")";
}

} // namespace VisionBIM::Geometry
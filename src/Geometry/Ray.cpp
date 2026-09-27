#include "Ray.h"
#include "Plane.h"     // для IntersectPlane
#include <ostream>
#include <cmath>

namespace VisionBIM::Geometry
{

Ray::Ray()
    : origin(0.0, 0.0, 0.0), direction(0.0, 0.0, -1.0)
{
}

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin(origin), direction(direction)
{
}

Vector3 Ray::PointAt(double t) const
{
    return origin + direction * t;
}

void Ray::Normalize()
{
    direction.Normalize();
}

Ray Ray::Normalized() const
{
    Ray result = *this;
    result.Normalize();
    return result;
}

Vector3 Ray::ProjectPoint(const Vector3& point) const
{
    Vector3 op = point - origin;
    double t = op.Dot(direction);

    if (t < 0.0)
        return origin;                    // перед началом луча

    return origin + direction * t;
}

double Ray::Distance(const Vector3& point) const
{
    Vector3 projection = ProjectPoint(point);
    return (point - projection).Length();
}

bool Ray::IntersectPlane(const Plane& plane, double& outT) const
{
    double denom = plane.normal.Dot(direction);

    if (std::abs(denom) < MathConstants::Epsilon)
        return false;                     // параллельно плоскости

    outT = -plane.SignedDistance(origin) / denom;

    return outT >= 0.0;                   // только вперёд по лучу
}

bool Ray::operator==(const Ray& other) const
{
    return origin == other.origin && direction == other.direction;
}

bool Ray::operator!=(const Ray& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
    return os << "Ray(origin: " << ray.origin << ", dir: " << ray.direction << ")";
}

} // namespace VisionBIM::Geometry
#include "Vector3.h"
#include <ostream>
#include <algorithm>

namespace VisionBIM::Geometry
{

Vector3::Vector3(double scalar)
    : x(scalar), y(scalar), z(scalar)
{
}

Vector3::Vector3(double x, double y, double z)
    : x(x), y(y), z(z)
{
}

double Vector3::Length() const
{
    return std::sqrt(LengthSquared());
}

double Vector3::LengthSquared() const
{
    return x * x + y * y + z * z;
}

void Vector3::Normalize()
{
    double len = Length();
    if (len > MathConstants::Epsilon)
    {
        x /= len;
        y /= len;
        z /= len;
    }
}

Vector3 Vector3::Normalized() const
{
    Vector3 result = *this;
    result.Normalize();
    return result;
}

double Vector3::Dot(const Vector3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::Cross(const Vector3& other) const
{
    return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

double Vector3::Angle(const Vector3& other) const
{
    double dot = Dot(other);
    double len1 = Length();
    double len2 = other.Length();

    if (len1 < MathConstants::Epsilon || len2 < MathConstants::Epsilon)
        return 0.0;

    double cosTheta = Math::Clamp(dot / (len1 * len2), -1.0, 1.0);
    return std::acos(cosTheta);
}

double Vector3::AngleDegrees(const Vector3& other) const
{
    return Math::RadiansToDegrees(Angle(other));
}

double Vector3::Distance(const Vector3& a, const Vector3& b)
{
    return (a - b).Length();
}

double Vector3::DistanceSquared(const Vector3& a, const Vector3& b)
{
    return (a - b).LengthSquared();
}

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, double t)
{
    return Vector3(
        Math::Lerp(a.x, b.x, t),
        Math::Lerp(a.y, b.y, t),
        Math::Lerp(a.z, b.z, t)
    );
}

Vector3 Vector3::Abs() const
{
    return Vector3(std::abs(x), std::abs(y), std::abs(z));
}

Vector3 Vector3::Min(const Vector3& a, const Vector3& b)
{
    return Vector3(
        std::min(a.x, b.x),
        std::min(a.y, b.y),
        std::min(a.z, b.z)
    );
}

Vector3 Vector3::Max(const Vector3& a, const Vector3& b)
{
    return Vector3(
        std::max(a.x, b.x),
        std::max(a.y, b.y),
        std::max(a.z, b.z)
    );
}

// ====================== Операторы ======================

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(double scalar) const
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(double scalar) const
{
    if (std::abs(scalar) < MathConstants::Epsilon)
        return Vector3();
    return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3& Vector3::operator*=(double scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3& Vector3::operator/=(double scalar)
{
    if (std::abs(scalar) > MathConstants::Epsilon)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }
    return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
    return Math::NearlyEqual(x, other.x) &&
           Math::NearlyEqual(y, other.y) &&
           Math::NearlyEqual(z, other.z);
}

bool Vector3::operator!=(const Vector3& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

} // namespace VisionBIM::Geometry
#include "Vector2.h"
#include <ostream>

namespace VisionBIM::Geometry
{

Vector2::Vector2(double scalar)
    : x(scalar), y(scalar)
{
}

Vector2::Vector2(double x, double y)
    : x(x), y(y)
{
}

double Vector2::Length() const
{
    return std::sqrt(LengthSquared());
}

double Vector2::LengthSquared() const
{
    return x * x + y * y;
}

void Vector2::Normalize()
{
    double len = Length();
    if (len > MathConstants::Epsilon)
    {
        x /= len;
        y /= len;
    }
}

Vector2 Vector2::Normalized() const
{
    Vector2 result = *this;
    result.Normalize();
    return result;
}

double Vector2::Dot(const Vector2& other) const
{
    return x * other.x + y * other.y;
}

double Vector2::Angle(const Vector2& other) const
{
    double dot = Dot(other);
    double len1 = Length();
    double len2 = other.Length();

    if (len1 < MathConstants::Epsilon || len2 < MathConstants::Epsilon)
        return 0.0;

    double cosTheta = Math::Clamp(dot / (len1 * len2), -1.0, 1.0);
    return std::acos(cosTheta);
}

double Vector2::AngleDegrees(const Vector2& other) const
{
    return Math::RadiansToDegrees(Angle(other));
}

Vector2 Vector2::Perpendicular() const
{
    return Vector2(-y, x);
}

Vector2 Vector2::PerpendicularCW() const
{
    return Vector2(y, -x);
}

double Vector2::Distance(const Vector2& a, const Vector2& b)
{
    return (a - b).Length();
}

double Vector2::DistanceSquared(const Vector2& a, const Vector2& b)
{
    return (a - b).LengthSquared();
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, double t)
{
    return Vector2(Math::Lerp(a.x, b.x, t),
                   Math::Lerp(a.y, b.y, t));
}

// ====================== Операторы ======================

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(double scalar) const
{
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(double scalar) const
{
    if (std::abs(scalar) < MathConstants::Epsilon)
        return Vector2();
    return Vector2(x / scalar, y / scalar);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator*=(double scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator/=(double scalar)
{
    if (std::abs(scalar) > MathConstants::Epsilon)
    {
        x /= scalar;
        y /= scalar;
    }
    return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
    return Math::NearlyEqual(x, other.x) && Math::NearlyEqual(y, other.y);
}

bool Vector2::operator!=(const Vector2& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
    return os << "(" << v.x << ", " << v.y << ")";
}

} // namespace VisionBIM::Geometry
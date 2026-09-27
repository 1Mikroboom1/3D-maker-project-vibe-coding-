#pragma once

#include "Vector2.h"
#include "Line2D.h"
#include "MathConstants.h"

namespace VisionBIM::Geometry
{

class Segment2D
{
public:
    Vector2 a;
    Vector2 b;

    Segment2D();
    Segment2D(const Vector2& a, const Vector2& b);

    [[nodiscard]] Vector2 Midpoint() const;
    [[nodiscard]] double Length() const;
    [[nodiscard]] double LengthSquared() const;

    [[nodiscard]] Line2D ToLine() const;

    // Проекция точки на отрезок (с ограничением концов)
    [[nodiscard]] Vector2 ProjectPoint(const Vector2& p) const;

    [[nodiscard]] double Distance(const Vector2& p) const;

    [[nodiscard]] bool Contains(const Vector2& p, double epsilon = MathConstants::Epsilon) const;

    // Пересечение двух отрезков
    [[nodiscard]] bool Intersects(const Segment2D& other, Vector2* intersectionPoint = nullptr) const;
};

} // namespace VisionBIM::Geometry
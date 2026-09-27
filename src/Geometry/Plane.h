#pragma once

#include "Vector3.h"
#include "MathConstants.h"
#include "MathUtils.h"

namespace VisionBIM::Geometry
{

class Plane
{
public:
    Vector3 normal;     // Нормаль плоскости (рекомендуется нормализованная)
    double distance;    // Расстояние от начала координат до плоскости (dot(normal, point))

    Plane();
    Plane(const Vector3& normal, double distance);
    Plane(const Vector3& normal, const Vector3& pointOnPlane);

    // Создание из трёх точек (против часовой стрелки)
    static Plane FromThreePoints(const Vector3& a, const Vector3& b, const Vector3& c);

    // Нормализация
    void Normalize();
    [[nodiscard]] Plane Normalized() const;

    // Расстояния
    [[nodiscard]] double SignedDistance(const Vector3& point) const;
    [[nodiscard]] double Distance(const Vector3& point) const;

    // Проекция точки на плоскость
    [[nodiscard]] Vector3 ProjectPoint(const Vector3& point) const;

    // Пересечение с лучом (t >= 0)
    [[nodiscard]] bool IntersectRay(const class Ray& ray, double& outT) const;

    // Основные операции
    [[nodiscard]] bool IsPointOnPlane(const Vector3& point, double epsilon = MathConstants::Epsilon) const;

    bool operator==(const Plane& other) const;
    bool operator!=(const Plane& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Plane& plane);
};

} // namespace VisionBIM::Geometry
#pragma once

#include "Vector3.h"
#include "MathConstants.h"
#include "MathUtils.h"

namespace VisionBIM::Geometry
{

class Ray
{
public:
    Vector3 origin;
    Vector3 direction;   // Рекомендуется нормализовать

    Ray();
    Ray(const Vector3& origin, const Vector3& direction);

    // Точка на луче: origin + t * direction (t >= 0)
    [[nodiscard]] Vector3 PointAt(double t) const;

    // Нормализация направления
    void Normalize();
    [[nodiscard]] Ray Normalized() const;

    // Расстояние от точки до луча
    [[nodiscard]] double Distance(const Vector3& point) const;

    // Проекция точки на луч (с ограничением t >= 0)
    [[nodiscard]] Vector3 ProjectPoint(const Vector3& point) const;

    // Пересечение с плоскостью (вернёт t, если пересечение существует)
    [[nodiscard]] bool IntersectPlane(const class Plane& plane, double& outT) const;

    bool operator==(const Ray& other) const;
    bool operator!=(const Ray& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
};

} // namespace VisionBIM::Geometry
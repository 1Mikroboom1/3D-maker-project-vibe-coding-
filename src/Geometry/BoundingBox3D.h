#pragma once

#include "Vector3.h"
#include "MathConstants.h"
#include "MathUtils.h"
#include <vector>

namespace VisionBIM::Geometry
{

class BoundingBox3D
{
public:
    Vector3 min;
    Vector3 max;

    BoundingBox3D();
    BoundingBox3D(const Vector3& min, const Vector3& max);

    // Фабричные методы
    static BoundingBox3D FromPoints(const Vector3* points, size_t count);
    static BoundingBox3D FromPoints(const std::vector<Vector3>& points);

    // Модификация
    void Expand(const Vector3& point);
    void Expand(const BoundingBox3D& other);
    void Reset();

    // Свойства
    [[nodiscard]] Vector3 Center() const;
    [[nodiscard]] Vector3 Size() const;
    [[nodiscard]] Vector3 Extents() const;        // half size
    [[nodiscard]] double Volume() const;

    [[nodiscard]] bool IsValid() const;
    [[nodiscard]] bool IsEmpty() const;

    // Тесты
    [[nodiscard]] bool Contains(const Vector3& point) const;
    [[nodiscard]] bool Contains(const BoundingBox3D& other) const;
    [[nodiscard]] bool Intersects(const BoundingBox3D& other) const;

    // Утилиты
    [[nodiscard]] Vector3 ClosestPoint(const Vector3& point) const;

    bool operator==(const BoundingBox3D& other) const;
    bool operator!=(const BoundingBox3D& other) const;

    friend std::ostream& operator<<(std::ostream& os, const BoundingBox3D& box);
};

} // namespace VisionBIM::Geometry
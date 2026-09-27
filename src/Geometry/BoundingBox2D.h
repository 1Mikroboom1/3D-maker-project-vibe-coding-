#pragma once

#include "Vector2.h"
#include "MathConstants.h"
#include "MathUtils.h"
#include <vector>

namespace VisionBIM::Geometry
{

class BoundingBox2D
{
public:
    Vector2 min;
    Vector2 max;

    BoundingBox2D();
    BoundingBox2D(const Vector2& min, const Vector2& max);

    // Фабричные методы
    static BoundingBox2D FromPoints(const Vector2* points, size_t count);
    static BoundingBox2D FromPoints(const std::vector<Vector2>& points);

    // Модификация
    void Expand(const Vector2& point);
    void Expand(const BoundingBox2D& other);
    void Reset(); // сбрасывает в пустое состояние

    // Свойства
    [[nodiscard]] Vector2 Center() const;
    [[nodiscard]] Vector2 Size() const;
    [[nodiscard]] Vector2 Extents() const;        // half size
    [[nodiscard]] double Area() const;

    [[nodiscard]] bool IsValid() const;           // min <= max
    [[nodiscard]] bool IsEmpty() const;

    // Тесты
    [[nodiscard]] bool Contains(const Vector2& point) const;
    [[nodiscard]] bool Contains(const BoundingBox2D& other) const;
    [[nodiscard]] bool Intersects(const BoundingBox2D& other) const;

    // Утилиты
    [[nodiscard]] Vector2 ClosestPoint(const Vector2& point) const;

    bool operator==(const BoundingBox2D& other) const;
    bool operator!=(const BoundingBox2D& other) const;

    friend std::ostream& operator<<(std::ostream& os, const BoundingBox2D& box);
};

} // namespace VisionBIM::Geometry
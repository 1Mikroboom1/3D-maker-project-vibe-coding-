#pragma once

#include "Vector2.h"
#include "BoundingBox2D.h"
#include "MathConstants.h"
#include "MathUtils.h"
#include <vector>

namespace VisionBIM::Geometry
{

class Polygon
{
public:
    std::vector<Vector2> vertices;

    Polygon() = default;
    explicit Polygon(const std::vector<Vector2>& verts);
    explicit Polygon(std::vector<Vector2>&& verts);

    void AddVertex(const Vector2& v);
    void Clear();

    [[nodiscard]] size_t VertexCount() const;
    [[nodiscard]] bool IsEmpty() const;
    [[nodiscard]] bool IsClosed() const;           // проверка, что первая и последняя точки совпадают

    // Основные геометрические свойства
    [[nodiscard]] double Area() const;
    [[nodiscard]] Vector2 Centroid() const;
    [[nodiscard]] BoundingBox2D GetBoundingBox() const;

    // Тесты
    [[nodiscard]] bool Contains(const Vector2& point, double epsilon = MathConstants::Epsilon) const; // Point-in-Polygon
    [[nodiscard]] bool IsConvex() const;

    // Утилиты
    [[nodiscard]] double Perimeter() const;
    void Simplify(double tolerance = 1e-6);        // Упрощение (Douglas-Peucker)
    void Reverse();                                // Изменить порядок вершин (ориентацию)

    // Статические фабричные методы
    static Polygon Rectangle(const Vector2& min, const Vector2& max);
    static Polygon Circle(const Vector2& center, double radius, int segments = 32);

    bool operator==(const Polygon& other) const;
    bool operator!=(const Polygon& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Polygon& poly);
};

} // namespace VisionBIM::Geometry
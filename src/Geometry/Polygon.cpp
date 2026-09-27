#include "Polygon.h"
#include <algorithm>
#include <numeric>
#include <cmath>

namespace VisionBIM::Geometry
{

Polygon::Polygon(const std::vector<Vector2>& verts)
    : vertices(verts)
{
}

Polygon::Polygon(std::vector<Vector2>&& verts)
    : vertices(std::move(verts))
{
}

void Polygon::AddVertex(const Vector2& v)
{
    vertices.push_back(v);
}

void Polygon::Clear()
{
    vertices.clear();
}

size_t Polygon::VertexCount() const
{
    return vertices.size();
}

bool Polygon::IsEmpty() const
{
    return vertices.size() < 3;
}

bool Polygon::IsClosed() const
{
    if (vertices.size() < 3) return false;
    return vertices.front() == vertices.back();
}

double Polygon::Area() const
{
    if (vertices.size() < 3) return 0.0;

    double area = 0.0;
    size_t n = vertices.size();

    for (size_t i = 0; i < n; ++i)
    {
        const Vector2& a = vertices[i];
        const Vector2& b = vertices[(i + 1) % n];
        area += a.x * b.y - b.x * a.y;
    }

    return std::abs(area) * 0.5;
}

Vector2 Polygon::Centroid() const
{
    if (vertices.size() < 3) return Vector2();

    Vector2 centroid(0.0);
    double area = 0.0;
    size_t n = vertices.size();

    for (size_t i = 0; i < n; ++i)
    {
        const Vector2& a = vertices[i];
        const Vector2& b = vertices[(i + 1) % n];
        double cross = a.x * b.y - b.x * a.y;
        area += cross;
        centroid += (a + b) * cross;
    }

    area *= 0.5;
    if (std::abs(area) > MathConstants::Epsilon)
        centroid /= (6.0 * area);

    return centroid;
}

BoundingBox2D Polygon::GetBoundingBox() const
{
    if (vertices.empty())
        return BoundingBox2D();

    return BoundingBox2D::FromPoints(vertices);
}

bool Polygon::Contains(const Vector2& point, double epsilon) const
{
    if (vertices.size() < 3) return false;

    // Ray casting algorithm
    bool inside = false;
    size_t n = vertices.size();

    for (size_t i = 0, j = n - 1; i < n; j = i++)
    {
        const Vector2& a = vertices[i];
        const Vector2& b = vertices[j];

        if (((a.y > point.y) != (b.y > point.y)) &&
            (point.x < a.x + (b.x - a.x) * (point.y - a.y) / (b.y - a.y + epsilon)))
        {
            inside = !inside;
        }
    }

    return inside;
}

bool Polygon::IsConvex() const
{
    if (vertices.size() < 3) return false;

    size_t n = vertices.size();
    bool isPositive = false;

    for (size_t i = 0; i < n; ++i)
    {
        Vector2 a = vertices[i];
        Vector2 b = vertices[(i + 1) % n];
        Vector2 c = vertices[(i + 2) % n];

        Vector2 ab = b - a;
        Vector2 bc = c - b;
        double cross = ab.x * bc.y - ab.y * bc.x;

        if (std::abs(cross) < MathConstants::Epsilon) continue;

        bool currentSign = cross > 0;
        if (!isPositive && cross != 0)
            isPositive = currentSign;
        else if (currentSign != isPositive)
            return false;
    }

    return true;
}

double Polygon::Perimeter() const
{
    if (vertices.size() < 2) return 0.0;

    double perimeter = 0.0;
    size_t n = vertices.size();

    for (size_t i = 0; i < n; ++i)
        perimeter += (vertices[i] - vertices[(i + 1) % n]).Length();

    return perimeter;
}

void Polygon::Reverse()
{
    std::reverse(vertices.begin(), vertices.end());
}

bool Polygon::operator==(const Polygon& other) const
{
    if (vertices.size() != other.vertices.size()) return false;
    for (size_t i = 0; i < vertices.size(); ++i)
        if (vertices[i] != other.vertices[i])
            return false;
    return true;
}

bool Polygon::operator!=(const Polygon& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Polygon& poly)
{
    os << "Polygon(vertices: " << poly.vertices.size() << ")\n";
    for (const auto& v : poly.vertices)
        os << "  " << v << "\n";
    return os;
}

// ====================== Фабричные методы ======================

Polygon Polygon::Rectangle(const Vector2& min, const Vector2& max)
{
    Polygon p;
    p.vertices = {
        {min.x, min.y},
        {max.x, min.y},
        {max.x, max.y},
        {min.x, max.y}
    };
    return p;
}

Polygon Polygon::Circle(const Vector2& center, double radius, int segments)
{
    Polygon p;
    if (segments < 3) segments = 3;

    for (int i = 0; i < segments; ++i)
    {
        double angle = i * MathConstants::TwoPi / segments;
        p.vertices.emplace_back(
            center.x + radius * std::cos(angle),
            center.y + radius * std::sin(angle)
        );
    }
    return p;
}

} // namespace VisionBIM::Geometry
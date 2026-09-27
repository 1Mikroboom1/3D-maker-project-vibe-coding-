#pragma once

#include <cmath>
#include <iosfwd>           // для std::ostream
#include "MathConstants.h"
#include "MathUtils.h"

namespace VisionBIM::Geometry
{

class Vector2
{
public:
    double x = 0.0;
    double y = 0.0;

    // Конструкторы
    Vector2() = default;
    explicit Vector2(double scalar);
    Vector2(double x, double y);

    // Длина
    [[nodiscard]] double Length() const;
    [[nodiscard]] double LengthSquared() const;

    // Нормализация
    void Normalize();
    [[nodiscard]] Vector2 Normalized() const;

    // Скалярные произведения и углы
    [[nodiscard]] double Dot(const Vector2& other) const;
    [[nodiscard]] double Angle(const Vector2& other) const;           // угол между векторами в радианах
    [[nodiscard]] double AngleDegrees(const Vector2& other) const;

    // Перпендикуляр
    [[nodiscard]] Vector2 Perpendicular() const;          // поворот на 90° против часовой
    [[nodiscard]] Vector2 PerpendicularCW() const;        // по часовой

    // Расстояние
    [[nodiscard]] static double Distance(const Vector2& a, const Vector2& b);
    [[nodiscard]] static double DistanceSquared(const Vector2& a, const Vector2& b);

    // Линейная интерполяция
    [[nodiscard]] static Vector2 Lerp(const Vector2& a, const Vector2& b, double t);

    // Операторы
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(double scalar) const;
    Vector2 operator/(double scalar) const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(double scalar);
    Vector2& operator/=(double scalar);

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;

    // Удобный вывод в консоль / логи
    friend std::ostream& operator<<(std::ostream& os, const Vector2& v);
};

} // namespace VisionBIM::Geometry
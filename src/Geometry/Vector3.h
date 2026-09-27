#pragma once

#include <cmath>
#include <iosfwd>
#include "MathConstants.h"
#include "MathUtils.h"

namespace VisionBIM::Geometry
{

class Vector3
{
public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    // Конструкторы
    Vector3() = default;
    explicit Vector3(double scalar);
    Vector3(double x, double y, double z);

    // Длина
    [[nodiscard]] double Length() const;
    [[nodiscard]] double LengthSquared() const;

    // Нормализация
    void Normalize();
    [[nodiscard]] Vector3 Normalized() const;

    // Скалярные и векторные произведения
    [[nodiscard]] double Dot(const Vector3& other) const;
    [[nodiscard]] Vector3 Cross(const Vector3& other) const;

    // Углы
    [[nodiscard]] double Angle(const Vector3& other) const;           // в радианах
    [[nodiscard]] double AngleDegrees(const Vector3& other) const;

    // Расстояния
    [[nodiscard]] static double Distance(const Vector3& a, const Vector3& b);
    [[nodiscard]] static double DistanceSquared(const Vector3& a, const Vector3& b);

    // Интерполяция
    [[nodiscard]] static Vector3 Lerp(const Vector3& a, const Vector3& b, double t);

    // Полезные утилиты
    [[nodiscard]] Vector3 Abs() const;
    [[nodiscard]] static Vector3 Min(const Vector3& a, const Vector3& b);
    [[nodiscard]] static Vector3 Max(const Vector3& a, const Vector3& b);

    // Операторы
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(double scalar) const;
    Vector3 operator/(double scalar) const;

    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator*=(double scalar);
    Vector3& operator/=(double scalar);

    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;

    // Удобный вывод
    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};

} // namespace VisionBIM::Geometry
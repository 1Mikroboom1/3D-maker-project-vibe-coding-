#pragma once

#include <array>
#include <iosfwd>
#include "Vector3.h"
#include "MathConstants.h"
#include "MathUtils.h"

namespace VisionBIM::Geometry
{

class Matrix4
{
public:
    // m[row][column] — row-major порядок
    std::array<std::array<double, 4>, 4> m{};

    // Конструкторы
    Matrix4();                                      // Identity matrix
    explicit Matrix4(double diagonal);

    // Фабричные методы
    static Matrix4 Identity();
    static Matrix4 Zero();

    static Matrix4 Translation(const Vector3& translation);
    static Matrix4 Scaling(const Vector3& scale);
    static Matrix4 Scaling(double uniformScale);

    static Matrix4 RotationX(double angleRad);
    static Matrix4 RotationY(double angleRad);
    static Matrix4 RotationZ(double angleRad);
    static Matrix4 RotationAxisAngle(const Vector3& axis, double angleRad);

    // Основные операции с матрицей
    [[nodiscard]] Matrix4 Transpose() const;
    [[nodiscard]] Matrix4 Inverse() const;           // Возвращает Zero() при вырожденной матрице
    [[nodiscard]] double Determinant() const;

    // Трансформация
    [[nodiscard]] Vector3 TransformPoint(const Vector3& point) const;      // с переносом
    [[nodiscard]] Vector3 TransformVector(const Vector3& vec) const;       // без переноса
    [[nodiscard]] Vector3 TransformDirection(const Vector3& dir) const;    // нормализованный вектор

    // Операторы
    Matrix4 operator*(const Matrix4& other) const;
    Vector3 operator*(const Vector3& v) const;        // TransformPoint

    Matrix4& operator*=(const Matrix4& other);

    bool operator==(const Matrix4& other) const;
    bool operator!=(const Matrix4& other) const;

    // Удобный вывод
    friend std::ostream& operator<<(std::ostream& os, const Matrix4& mat);
};

} // namespace VisionBIM::Geometry
#pragma once

#include "Vector3.h"
#include "Matrix4.h"
#include "MathConstants.h"
#include "MathUtils.h"

namespace VisionBIM::Geometry
{

class Transform
{
public:
    Vector3 position = Vector3(0.0);
    Vector3 scale    = Vector3(1.0);
    // Quaternion rotation; // можно добавить позже

    Transform() = default;
    explicit Transform(const Vector3& position);
    Transform(const Vector3& position, const Vector3& scale);

    // Основные матрицы трансформации
    [[nodiscard]] Matrix4 GetMatrix() const;
    [[nodiscard]] Matrix4 GetInverseMatrix() const;

    // Применение трансформации
    [[nodiscard]] Vector3 TransformPoint(const Vector3& point) const;
    [[nodiscard]] Vector3 TransformVector(const Vector3& vec) const;      // без переноса
    [[nodiscard]] Vector3 TransformDirection(const Vector3& dir) const;

    [[nodiscard]] Vector3 InverseTransformPoint(const Vector3& point) const;
    [[nodiscard]] Vector3 InverseTransformVector(const Vector3& vec) const;

    // Утилиты
    void Translate(const Vector3& delta);
    void SetScale(const Vector3& newScale);

    bool operator==(const Transform& other) const;
    bool operator!=(const Transform& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Transform& t);
};

} // namespace VisionBIM::Geometry
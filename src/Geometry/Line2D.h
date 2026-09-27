#pragma once

#include "Vector2.h"
#include "MathConstants.h"
#include "MathUtils.h"

namespace VisionBIM::Geometry
{

class Line2D
{
public:
    Vector2 point;      // Точка, лежащая на прямой
    Vector2 direction;  // Направляющий вектор (не обязательно нормализованный)

    Line2D();
    Line2D(const Vector2& point, const Vector2& direction);

    // Создание из двух точек
    static Line2D FromTwoPoints(const Vector2& a, const Vector2& b);

    // Основные операции
    [[nodiscard]] Vector2 ProjectPoint(const Vector2& p) const;     // Проекция точки на прямую
    [[nodiscard]] double Distance(const Vector2& p) const;          // Расстояние от точки до прямой

    [[nodiscard]] double Angle(const Line2D& other) const;          // Угол между прямыми (радианы)
    [[nodiscard]] double AngleDegrees(const Line2D& other) const;

    [[nodiscard]] bool IsParallel(const Line2D& other) const;
    [[nodiscard]] bool IsCoincident(const Line2D& other) const;     // Совпадают ли прямые

    // Нормализация направления (опционально)
    void NormalizeDirection();
    [[nodiscard]] Line2D Normalized() const;
};

} // namespace VisionBIM::Geometry
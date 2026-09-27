#pragma once

#include <algorithm>
#include <cmath>

#include "MathConstants.h"

namespace VisionBIM::Geometry
{
    namespace Math
    {
        //============================================================
        // Проверка на приблизительное равенство
        //============================================================

        [[nodiscard]]
        inline bool NearlyEqual(
            double a,
            double b,
            double epsilon = MathConstants::Epsilon)
        {
            return std::abs(a - b) <= epsilon;
        }

        //============================================================
        // Ограничение значения диапазоном
        //============================================================

        template<typename T>
        [[nodiscard]]
        inline T Clamp(
            const T& value,
            const T& minimum,
            const T& maximum)
        {
            return std::clamp(value, minimum, maximum);
        }

        //============================================================
        // Линейная интерполяция
        //============================================================

        template<typename T>
        [[nodiscard]]
        inline T Lerp(
            const T& a,
            const T& b,
            double t)
        {
            return a + (b - a) * t;
        }

        //============================================================
        // Перевод градусов в радианы
        //============================================================

        [[nodiscard]]
        inline double DegreesToRadians(double degrees)
        {
            return degrees * MathConstants::DegToRad;
        }

        //============================================================
        // Перевод радиан в градусы
        //============================================================

        [[nodiscard]]
        inline double RadiansToDegrees(double radians)
        {
            return radians * MathConstants::RadToDeg;
        }

        //============================================================
        // Квадрат числа
        //============================================================

        template<typename T>
        [[nodiscard]]
        inline T Square(const T& value)
        {
            return value * value;
        }

        //============================================================
        // Знак числа
        //============================================================

        template<typename T>
        [[nodiscard]]
        inline int Sign(const T& value)
        {
            return (T(0) < value) - (value < T(0));
        }

        //============================================================
        // Проверка попадания в диапазон
        //============================================================

        template<typename T>
        [[nodiscard]]
        inline bool IsBetween(
            const T& value,
            const T& minimum,
            const T& maximum)
        {
            return value >= minimum && value <= maximum;
        }

        //============================================================
        // Нормализация значения
        //============================================================

        [[nodiscard]]
        inline double Normalize(
            double value,
            double minimum,
            double maximum)
        {
            return (value - minimum) / (maximum - minimum);
        }

        //============================================================
        // Ограничение значения диапазоном [0..1]
        //============================================================

        [[nodiscard]]
        inline double Saturate(double value)
        {
            return Clamp(value, 0.0, 1.0);
        }
    }
}
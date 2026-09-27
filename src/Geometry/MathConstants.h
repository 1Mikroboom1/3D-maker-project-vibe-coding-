#pragma once

#include <limits>

namespace VisionBIM::Geometry
{
    namespace MathConstants
    {
        // Основные математические константы
        constexpr double Pi      = 3.14159265358979323846;
        constexpr double TwoPi   = 2.0 * Pi;
        constexpr double HalfPi  = Pi * 0.5;

        constexpr double E = 2.71828182845904523536;

        // Коэффициенты перевода углов
        constexpr double DegToRad = Pi / 180.0;
        constexpr double RadToDeg = 180.0 / Pi;

        // Допустимая погрешность сравнения
        constexpr double Epsilon = 1e-9;

        // Минимальное и максимальное значение double
        constexpr double MinDouble = std::numeric_limits<double>::lowest();
        constexpr double MaxDouble = std::numeric_limits<double>::max();
    }
}
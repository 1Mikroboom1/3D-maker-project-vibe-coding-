#include "Matrix4.h"
#include <ostream>
#include <cmath>
#include <algorithm>

namespace VisionBIM::Geometry
{

// ==================== Конструкторы и фабрики ====================

Matrix4::Matrix4()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m[i][j] = (i == j) ? 1.0 : 0.0;
}

Matrix4::Matrix4(double diagonal)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m[i][j] = (i == j) ? diagonal : 0.0;
}

Matrix4 Matrix4::Identity()
{
    return Matrix4(1.0);
}

Matrix4 Matrix4::Zero()
{
    return Matrix4(0.0);
}

Matrix4 Matrix4::Translation(const Vector3& t)
{
    Matrix4 mat = Identity();
    mat.m[0][3] = t.x;
    mat.m[1][3] = t.y;
    mat.m[2][3] = t.z;
    return mat;
}

Matrix4 Matrix4::Scaling(const Vector3& s)
{
    Matrix4 mat = Identity();
    mat.m[0][0] = s.x;
    mat.m[1][1] = s.y;
    mat.m[2][2] = s.z;
    return mat;
}

Matrix4 Matrix4::Scaling(double uniformScale)
{
    return Scaling(Vector3(uniformScale));
}

Matrix4 Matrix4::RotationX(double angleRad)
{
    const double c = std::cos(angleRad);
    const double s = std::sin(angleRad);
    Matrix4 mat = Identity();
    mat.m[1][1] = c;  mat.m[1][2] = -s;
    mat.m[2][1] = s;  mat.m[2][2] = c;
    return mat;
}

Matrix4 Matrix4::RotationY(double angleRad)
{
    const double c = std::cos(angleRad);
    const double s = std::sin(angleRad);
    Matrix4 mat = Identity();
    mat.m[0][0] = c;  mat.m[0][2] = s;
    mat.m[2][0] = -s; mat.m[2][2] = c;
    return mat;
}

Matrix4 Matrix4::RotationZ(double angleRad)
{
    const double c = std::cos(angleRad);
    const double s = std::sin(angleRad);
    Matrix4 mat = Identity();
    mat.m[0][0] = c;  mat.m[0][1] = -s;
    mat.m[1][0] = s;  mat.m[1][1] = c;
    return mat;
}

Matrix4 Matrix4::RotationAxisAngle(const Vector3& axis, double angleRad)
{
    Vector3 a = axis.Normalized();
    const double c = std::cos(angleRad);
    const double s = std::sin(angleRad);
    const double t = 1.0 - c;

    Matrix4 mat = Identity();

    mat.m[0][0] = c + a.x * a.x * t;
    mat.m[0][1] = a.x * a.y * t - a.z * s;
    mat.m[0][2] = a.x * a.z * t + a.y * s;

    mat.m[1][0] = a.y * a.x * t + a.z * s;
    mat.m[1][1] = c + a.y * a.y * t;
    mat.m[1][2] = a.y * a.z * t - a.x * s;

    mat.m[2][0] = a.z * a.x * t - a.y * s;
    mat.m[2][1] = a.z * a.y * t + a.x * s;
    mat.m[2][2] = c + a.z * a.z * t;

    return mat;
}

// ====================== Основные операции ======================

Matrix4 Matrix4::Transpose() const
{
    Matrix4 result;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            result.m[i][j] = m[j][i];
    return result;
}

double Matrix4::Determinant() const
{
    double a = m[0][0], b = m[0][1], c = m[0][2], d = m[0][3];
    double e = m[1][0], f = m[1][1], g = m[1][2], h = m[1][3];
    double i = m[2][0], j = m[2][1], k = m[2][2], l = m[2][3];
    double mm = m[3][0], n = m[3][1], o = m[3][2], p = m[3][3];

    return a * (f * (k * p - l * o) - g * (j * p - l * n) + h * (j * o - k * n)) -
           b * (e * (k * p - l * o) - g * (i * p - l * mm) + h * (i * o - k * mm)) +
           c * (e * (j * p - l * n) - f * (i * p - l * mm) + h * (i * n - j * mm)) -
           d * (e * (j * o - k * n) - f * (i * o - k * mm) + g * (i * n - j * mm));
}

Matrix4 Matrix4::Inverse() const
{
    double det = Determinant();
    if (std::abs(det) < MathConstants::Epsilon)
        return Zero();

    Matrix4 inv;

    auto Minor = [&](int row, int col) -> double {
        double sub[3][3];
        int subi = 0;
        for (int i = 0; i < 4; ++i) {
            if (i == row) continue;
            int subj = 0;
            for (int j = 0; j < 4; ++j) {
                if (j == col) continue;
                sub[subi][subj] = m[i][j];
                ++subj;
            }
            ++subi;
        }

        return sub[0][0] * (sub[1][1] * sub[2][2] - sub[2][1] * sub[1][2]) -
               sub[0][1] * (sub[1][0] * sub[2][2] - sub[2][0] * sub[1][2]) +
               sub[0][2] * (sub[1][0] * sub[2][1] - sub[2][0] * sub[1][1]);
    };

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            inv.m[j][i] = sign * Minor(i, j) / det;
        }
    }

    return inv;
}

// ====================== Трансформация ======================

Vector3 Matrix4::TransformPoint(const Vector3& p) const
{
    return Vector3(
        m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z + m[0][3],
        m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z + m[1][3],
        m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z + m[2][3]
    );
}

Vector3 Matrix4::TransformVector(const Vector3& v) const
{
    return Vector3(
        m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
        m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
        m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
    );
}

Vector3 Matrix4::TransformDirection(const Vector3& dir) const
{
    Vector3 result = TransformVector(dir);
    return result.Normalized();
}

// ====================== Операторы ======================

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
    Matrix4 result;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            double sum = 0.0;
            for (int k = 0; k < 4; ++k)
                sum += m[i][k] * other.m[k][j];
            result.m[i][j] = sum;
        }
    return result;
}

Vector3 Matrix4::operator*(const Vector3& v) const
{
    return TransformPoint(v);
}

Matrix4& Matrix4::operator*=(const Matrix4& other)
{
    *this = *this * other;
    return *this;
}

bool Matrix4::operator==(const Matrix4& other) const
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (!Math::NearlyEqual(m[i][j], other.m[i][j]))
                return false;
    return true;
}

bool Matrix4::operator!=(const Matrix4& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Matrix4& mat)
{
    os << "Matrix4:\n";
    for (int i = 0; i < 4; ++i) {
        os << "  [ ";
        for (int j = 0; j < 4; ++j) {
            os << mat.m[i][j];
            if (j < 3) os << ", ";
        }
        os << " ]\n";
    }
    return os;
}

} // namespace VisionBIM::Geometry
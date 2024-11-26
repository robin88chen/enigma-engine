#include "Matrix2.hpp"
#include "Vector2.hpp"
#include "MathGlobal.hpp"
#include "Radian.hpp"
#include <cassert>
#include <cmath>

using namespace Math;

Matrix2::Matrix2() : m_entry{ {0.0f, 0.0f}, {0.0f, 0.0f} }
{
}

Matrix2::Matrix2(float m00, float m01, float m10, float m11) : m_entry{ {m00, m01}, {m10, m11} }
{
}

Matrix2::Matrix2(const std::array<float, 4>& m) : m_entry{ {m[0], m[1]}, {m[2], m[3]} }
{
}

Matrix2 Matrix2::makeZero()
{
    return { 0.0f, 0.0f, 0.0f, 0.0f };
}

Matrix2 Matrix2::makeIdentity()
{
    return { 1.0f, 0.0f, 0.0f, 1.0f };
}

Matrix2 Matrix2::makeDiagonal(float m00, float m11)
{
    return { m00, 0.0f, 0.0f, m11 };
}

Matrix2 Matrix2::fromAngle(const Radian& angle)
{
    const float c = std::cos(angle.value());
    const float s = std::sin(angle.value());
    return { c, -s, s, c };
}

Matrix2::operator const float* () const
{
    return &m_entry[0][0];
}

Matrix2::operator float* ()
{
    return &m_entry[0][0];
}

const float* Matrix2::operator[] (unsigned row) const
{
    return m_entry[row];
}

float* Matrix2::operator[] (unsigned row)
{
    return m_entry[row];
}

float Matrix2::operator() (unsigned row, unsigned col) const
{
    return m_entry[row][col];
}

float& Matrix2::operator() (unsigned row, unsigned col)
{
    return m_entry[row][col];
}

void Matrix2::setRow(unsigned row, const Vector2& v)
{
    assert(row <= 1);
    m_entry[row][0] = v.x();
    m_entry[row][1] = v.y();
}

Vector2 Matrix2::getRow(int row) const
{
    assert(row <= 1);
    return { m_entry[row][0], m_entry[row][1] };
}

void Matrix2::setColumn(int col, const Vector2& v)
{
    assert(col <= 1);
    m_entry[0][col] = v.x();
    m_entry[1][col] = v.y();
}

Vector2 Matrix2::getColumn(int col) const
{
    assert(col <= 1);
    return { m_entry[0][col], m_entry[1][col] };
}

bool Matrix2::operator== (const Matrix2& mx) const
{
    return FloatCompare::isEqual(m_entry[0][0], mx.m_entry[0][0])
        && FloatCompare::isEqual(m_entry[0][1], mx.m_entry[0][1])
        && FloatCompare::isEqual(m_entry[1][0], mx.m_entry[1][0])
        && FloatCompare::isEqual(m_entry[1][1], mx.m_entry[1][1]);
}

bool Matrix2::operator!= (const Matrix2& mx) const
{
    return !(*this == mx);
}

Matrix2 Matrix2::operator+ (const Matrix2& mx) const
{
    return { m_entry[0][0] + mx.m_entry[0][0],
        m_entry[0][1] + mx.m_entry[0][1],
        m_entry[1][0] + mx.m_entry[1][0],
        m_entry[1][1] + mx.m_entry[1][1] };
}

Matrix2 Matrix2::operator- (const Matrix2& mx) const
{
    return { m_entry[0][0] - mx.m_entry[0][0],
        m_entry[0][1] - mx.m_entry[0][1],
        m_entry[1][0] - mx.m_entry[1][0],
        m_entry[1][1] - mx.m_entry[1][1] };
}

Matrix2 Matrix2::operator* (const Matrix2& mx) const
{
    return { m_entry[0][0] * mx.m_entry[0][0] + m_entry[0][1] * mx.m_entry[1][0],
        m_entry[0][0] * mx.m_entry[0][1] + m_entry[0][1] * mx.m_entry[1][1],
        m_entry[1][0] * mx.m_entry[0][0] + m_entry[1][1] * mx.m_entry[1][0],
        m_entry[1][0] * mx.m_entry[0][1] + m_entry[1][1] * mx.m_entry[1][1] };
}

Matrix2 Matrix2::operator* (float scalar) const
{
    return { m_entry[0][0] * scalar, m_entry[0][1] * scalar,
        m_entry[1][0] * scalar, m_entry[1][1] * scalar };
}

Matrix2 Matrix2::operator/ (float scalar) const
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    const float inv_scalar = 1.0f / scalar;
    return { m_entry[0][0] * inv_scalar, m_entry[0][1] * inv_scalar,
        m_entry[1][0] * inv_scalar, m_entry[1][1] * inv_scalar };
}

Matrix2 Matrix2::operator- () const
{
    return { -m_entry[0][0], -m_entry[0][1], -m_entry[1][0], -m_entry[1][1] };
}

Matrix2& Matrix2::operator+= (const Matrix2& mx)
{
    m_entry[0][0] += mx.m_entry[0][0];
    m_entry[0][1] += mx.m_entry[0][1];
    m_entry[1][0] += mx.m_entry[1][0];
    m_entry[1][1] += mx.m_entry[1][1];
    return *this;
}

Matrix2& Matrix2::operator-= (const Matrix2& mx)
{
    m_entry[0][0] -= mx.m_entry[0][0];
    m_entry[0][1] -= mx.m_entry[0][1];
    m_entry[1][0] -= mx.m_entry[1][0];
    m_entry[1][1] -= mx.m_entry[1][1];
    return *this;
}

Matrix2& Matrix2::operator*= (float scalar)
{
    m_entry[0][0] *= scalar;
    m_entry[0][1] *= scalar;
    m_entry[1][0] *= scalar;
    m_entry[1][1] *= scalar;
    return *this;
}

Matrix2& Matrix2::operator/= (float scalar)
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    const float inv_scalar = 1.0f / scalar;
    m_entry[0][0] *= inv_scalar;
    m_entry[0][1] *= inv_scalar;
    m_entry[1][0] *= inv_scalar;
    m_entry[1][1] *= inv_scalar;
    return *this;
}

Vector2 Matrix2::operator*(const Vector2& v) const
{
    return { m_entry[0][0] * v.x() + m_entry[0][1] * v.y(),
        m_entry[1][0] * v.x() + m_entry[1][1] * v.y() };
}

Matrix2 Matrix2::transpose() const
{
    return { m_entry[0][0], m_entry[1][0], m_entry[0][1], m_entry[1][1] };
}

Matrix2 Matrix2::inverse() const
{
    const float det = determinant();
    assert(!FloatCompare::isEqual(det, 0.0f));
    const float inv_det = 1.0f / det;
    return { m_entry[1][1] * inv_det, -m_entry[0][1] * inv_det,
        -m_entry[1][0] * inv_det, m_entry[0][0] * inv_det };
}

Matrix2 Matrix2::adjoint() const
{
    return { m_entry[1][1], -m_entry[0][1], -m_entry[1][0], m_entry[0][0] };
}

float Matrix2::determinant() const
{
    return m_entry[0][0] * m_entry[1][1] - m_entry[0][1] * m_entry[1][0];
}

Radian Matrix2::rotationAngle() const
{
    assert(FloatCompare::isEqual(m_entry[0][0] * m_entry[1][0] + m_entry[0][1] * m_entry[1][1], 0.0f));
    return Radian{ std::atan2(m_entry[1][0], m_entry[0][0]) };
}


const Matrix2 Matrix2::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const Matrix2 Matrix2::IDENTITY(1.0f, 0.0f, 0.0f, 1.0f);

namespace Math
{
    Matrix2 operator* (float scalar, const Matrix2& mx)
    {
        return mx * scalar;
    }
}

#include "Matrix4.hpp"
#include "EigenDecompose.hpp"
#include "Matrix3.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Point3.hpp"
#include "MathGlobal.hpp"
#include "Radian.hpp"
#include "Quaternion.hpp"
#include <cassert>
#include <cmath>
#include <algorithm>

using namespace Math;

Matrix4::Matrix4() : m_entry{ { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f } }
{
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33)
    : m_entry{ { m00, m01, m02, m03 }, { m10, m11, m12, m13 }, { m20, m21, m22, m23 }, { m30, m31, m32, m33 } }
{
}

// NOLINTNEXTLINE
Matrix4::Matrix4(const std::array<float, 16>& m) : m_entry{ { m[0], m[1], m[2], m[3] }, { m[4], m[5], m[6], m[7] }, { m[8], m[9], m[10], m[11] }, { m[12], m[13], m[14], m[15] } }
{
}

Matrix4::Matrix4(const Matrix3& mx) : m_entry{ { mx[0][0], mx[0][1], mx[0][2], 0.0f }, { mx[1][0], mx[1][1], mx[1][2], 0.0f }, { mx[2][0], mx[2][1], mx[2][2], 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f } }
{
}

Matrix4::Matrix4(const Matrix3& rotation_matrix, const Point3& position)
    : m_entry{ { rotation_matrix[0][0], rotation_matrix[0][1], rotation_matrix[0][2], position.x() },
        { rotation_matrix[1][0], rotation_matrix[1][1], rotation_matrix[1][2], position.y() },
        { rotation_matrix[2][0], rotation_matrix[2][1], rotation_matrix[2][2], position.z() },
        { 0.0f, 0.0f, 0.0f, 1.0f } }
{
}

Matrix4 Matrix4::makeZero()
{
    return {};
}

Matrix4 Matrix4::makeIdentity()
{
    return { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4::operator const float* () const
{
    return &m_entry[0][0];
}

Matrix4::operator float* ()
{
    return &m_entry[0][0];
}

const float* Matrix4::operator[] (unsigned row) const
{
    assert(row <= 3);
    return m_entry[row];
}

float* Matrix4::operator[] (unsigned row)
{
    assert(row <= 3);
    return m_entry[row];
}

float Matrix4::operator() (unsigned row, unsigned col) const
{
    assert(row <= 3);
    assert(col <= 3);
    return m_entry[row][col];
}

void Matrix4::setRow(unsigned row, const Vector4& vec)
{
    assert(row <= 3);
    m_entry[row][0] = vec.x();
    m_entry[row][1] = vec.y();
    m_entry[row][2] = vec.z();
    m_entry[row][3] = vec.w();
}

Vector4 Matrix4::getRow(unsigned row) const
{
    assert(row <= 3);
    return { m_entry[row][0], m_entry[row][1], m_entry[row][2], m_entry[row][3] };
}

void Matrix4::setColumn(unsigned col, const Vector4& vec)
{
    assert(col <= 3);
    m_entry[0][col] = vec.x();
    m_entry[1][col] = vec.y();
    m_entry[2][col] = vec.z();
    m_entry[3][col] = vec.w();
}

Vector4 Matrix4::getColumn(unsigned col) const
{
    assert(col <= 3);
    return { m_entry[0][col], m_entry[1][col], m_entry[2][col], m_entry[3][col] };
}

Matrix4& Matrix4::operator=(const Matrix3& mx)
{
    m_entry[0][0] = mx[0][0];
    m_entry[0][1] = mx[0][1];
    m_entry[0][2] = mx[0][2];
    m_entry[0][3] = 0.0f;
    m_entry[1][0] = mx[1][0];
    m_entry[1][1] = mx[1][1];
    m_entry[1][2] = mx[1][2];
    m_entry[1][3] = 0.0f;
    m_entry[2][0] = mx[2][0];
    m_entry[2][1] = mx[2][1];
    m_entry[2][2] = mx[2][2];
    m_entry[2][3] = 0.0f;
    m_entry[3][0] = 0.0f;
    m_entry[3][1] = 0.0f;
    m_entry[3][2] = 0.0f;
    m_entry[3][3] = 1.0f;
    return *this;
}

bool Matrix4::operator==(const Matrix4& mx) const
{
    return ((FloatCompare::isEqual(m_entry[0][0], mx.m_entry[0][0])) && (FloatCompare::isEqual(m_entry[0][1], mx.m_entry[0][1]))
        && (FloatCompare::isEqual(m_entry[0][2], mx.m_entry[0][2])) && (FloatCompare::isEqual(m_entry[0][3], mx.m_entry[0][3]))
        && (FloatCompare::isEqual(m_entry[1][0], mx.m_entry[1][0])) && (FloatCompare::isEqual(m_entry[1][1], mx.m_entry[1][1]))
        && (FloatCompare::isEqual(m_entry[1][2], mx.m_entry[1][2])) && (FloatCompare::isEqual(m_entry[1][3], mx.m_entry[1][3]))
        && (FloatCompare::isEqual(m_entry[2][0], mx.m_entry[2][0])) && (FloatCompare::isEqual(m_entry[2][1], mx.m_entry[2][1]))
        && (FloatCompare::isEqual(m_entry[2][2], mx.m_entry[2][2])) && (FloatCompare::isEqual(m_entry[2][3], mx.m_entry[2][3]))
        && (FloatCompare::isEqual(m_entry[3][0], mx.m_entry[3][0])) && (FloatCompare::isEqual(m_entry[3][1], mx.m_entry[3][1]))
        && (FloatCompare::isEqual(m_entry[3][2], mx.m_entry[3][2])) && (FloatCompare::isEqual(m_entry[3][3], mx.m_entry[3][3])));
}

bool Matrix4::operator!=(const Matrix4& mx) const
{
    return !(*this == mx);
}

Matrix4 Matrix4::operator+(const Matrix4& mx) const
{
    return { m_entry[0][0] + mx.m_entry[0][0], m_entry[0][1] + mx.m_entry[0][1], m_entry[0][2] + mx.m_entry[0][2], m_entry[0][3] + mx.m_entry[0][3],
        m_entry[1][0] + mx.m_entry[1][0], m_entry[1][1] + mx.m_entry[1][1], m_entry[1][2] + mx.m_entry[1][2], m_entry[1][3] + mx.m_entry[1][3],
        m_entry[2][0] + mx.m_entry[2][0], m_entry[2][1] + mx.m_entry[2][1], m_entry[2][2] + mx.m_entry[2][2], m_entry[2][3] + mx.m_entry[2][3],
        m_entry[3][0] + mx.m_entry[3][0], m_entry[3][1] + mx.m_entry[3][1], m_entry[3][2] + mx.m_entry[3][2], m_entry[3][3] + mx.m_entry[3][3] };
}

Matrix4 Matrix4::operator-(const Matrix4& mx) const
{
    return { m_entry[0][0] - mx.m_entry[0][0], m_entry[0][1] - mx.m_entry[0][1], m_entry[0][2] - mx.m_entry[0][2], m_entry[0][3] - mx.m_entry[0][3],
        m_entry[1][0] - mx.m_entry[1][0], m_entry[1][1] - mx.m_entry[1][1], m_entry[1][2] - mx.m_entry[1][2], m_entry[1][3] - mx.m_entry[1][3],
        m_entry[2][0] - mx.m_entry[2][0], m_entry[2][1] - mx.m_entry[2][1], m_entry[2][2] - mx.m_entry[2][2], m_entry[2][3] - mx.m_entry[2][3],
        m_entry[3][0] - mx.m_entry[3][0], m_entry[3][1] - mx.m_entry[3][1], m_entry[3][2] - mx.m_entry[3][2], m_entry[3][3] - mx.m_entry[3][3] };
}

Matrix4 Matrix4::operator*(const Matrix4& mx) const
{
    return { m_entry[0][0] * mx.m_entry[0][0] + m_entry[0][1] * mx.m_entry[1][0] + m_entry[0][2] * mx.m_entry[2][0] + m_entry[0][3] * mx.m_entry[3][0],
        m_entry[0][0] * mx.m_entry[0][1] + m_entry[0][1] * mx.m_entry[1][1] + m_entry[0][2] * mx.m_entry[2][1] + m_entry[0][3] * mx.m_entry[3][1],
        m_entry[0][0] * mx.m_entry[0][2] + m_entry[0][1] * mx.m_entry[1][2] + m_entry[0][2] * mx.m_entry[2][2] + m_entry[0][3] * mx.m_entry[3][2],
        m_entry[0][0] * mx.m_entry[0][3] + m_entry[0][1] * mx.m_entry[1][3] + m_entry[0][2] * mx.m_entry[2][3] + m_entry[0][3] * mx.m_entry[3][3],
        m_entry[1][0] * mx.m_entry[0][0] + m_entry[1][1] * mx.m_entry[1][0] + m_entry[1][2] * mx.m_entry[2][0] + m_entry[1][3] * mx.m_entry[3][0],
        m_entry[1][0] * mx.m_entry[0][1] + m_entry[1][1] * mx.m_entry[1][1] + m_entry[1][2] * mx.m_entry[2][1] + m_entry[1][3] * mx.m_entry[3][1],
        m_entry[1][0] * mx.m_entry[0][2] + m_entry[1][1] * mx.m_entry[1][2] + m_entry[1][2] * mx.m_entry[2][2] + m_entry[1][3] * mx.m_entry[3][2],
        m_entry[1][0] * mx.m_entry[0][3] + m_entry[1][1] * mx.m_entry[1][3] + m_entry[1][2] * mx.m_entry[2][3] + m_entry[1][3] * mx.m_entry[3][3],
        m_entry[2][0] * mx.m_entry[0][0] + m_entry[2][1] * mx.m_entry[1][0] + m_entry[2][2] * mx.m_entry[2][0] + m_entry[2][3] * mx.m_entry[3][0],
        m_entry[2][0] * mx.m_entry[0][1] + m_entry[2][1] * mx.m_entry[1][1] + m_entry[2][2] * mx.m_entry[2][1] + m_entry[2][3] * mx.m_entry[3][1],
        m_entry[2][0] * mx.m_entry[0][2] + m_entry[2][1] * mx.m_entry[1][2] + m_entry[2][2] * mx.m_entry[2][2] + m_entry[2][3] * mx.m_entry[3][2],
        m_entry[2][0] * mx.m_entry[0][3] + m_entry[2][1] * mx.m_entry[1][3] + m_entry[2][2] * mx.m_entry[2][3] + m_entry[2][3] * mx.m_entry[3][3],
        m_entry[3][0] * mx.m_entry[0][0] + m_entry[3][1] * mx.m_entry[1][0] + m_entry[3][2] * mx.m_entry[2][0] + m_entry[3][3] * mx.m_entry[3][0],
        m_entry[3][0] * mx.m_entry[0][1] + m_entry[3][1] * mx.m_entry[1][1] + m_entry[3][2] * mx.m_entry[2][1] + m_entry[3][3] * mx.m_entry[3][1],
        m_entry[3][0] * mx.m_entry[0][2] + m_entry[3][1] * mx.m_entry[1][2] + m_entry[3][2] * mx.m_entry[2][2] + m_entry[3][3] * mx.m_entry[3][2],
        m_entry[3][0] * mx.m_entry[0][3] + m_entry[3][1] * mx.m_entry[1][3] + m_entry[3][2] * mx.m_entry[2][3] + m_entry[3][3] * mx.m_entry[3][3]
    };
}

Matrix4 Matrix4::operator*(float scalar) const
{
    return { m_entry[0][0] * scalar, m_entry[0][1] * scalar, m_entry[0][2] * scalar, m_entry[0][3] * scalar,
        m_entry[1][0] * scalar, m_entry[1][1] * scalar, m_entry[1][2] * scalar, m_entry[1][3] * scalar,
        m_entry[2][0] * scalar, m_entry[2][1] * scalar, m_entry[2][2] * scalar, m_entry[2][3] * scalar,
        m_entry[3][0] * scalar, m_entry[3][1] * scalar, m_entry[3][2] * scalar, m_entry[3][3] * scalar };
}

Matrix4 Matrix4::operator/(float scalar) const
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    const float inv = 1.0f / scalar;
    return { m_entry[0][0] * inv, m_entry[0][1] * inv, m_entry[0][2] * inv, m_entry[0][3] * inv,
        m_entry[1][0] * inv, m_entry[1][1] * inv, m_entry[1][2] * inv, m_entry[1][3] * inv,
        m_entry[2][0] * inv, m_entry[2][1] * inv, m_entry[2][2] * inv, m_entry[2][3] * inv,
        m_entry[3][0] * inv, m_entry[3][1] * inv, m_entry[3][2] * inv, m_entry[3][3] * inv };
}

Matrix4 Matrix4::operator-() const
{
    return { -m_entry[0][0], -m_entry[0][1], -m_entry[0][2], -m_entry[0][3],
        -m_entry[1][0], -m_entry[1][1], -m_entry[1][2], -m_entry[1][3],
        -m_entry[2][0], -m_entry[2][1], -m_entry[2][2], -m_entry[2][3],
        -m_entry[3][0], -m_entry[3][1], -m_entry[3][2], -m_entry[3][3] };
}

Matrix4& Matrix4::operator+=(const Matrix4& mx)
{
    m_entry[0][0] += mx.m_entry[0][0];
    m_entry[0][1] += mx.m_entry[0][1];
    m_entry[0][2] += mx.m_entry[0][2];
    m_entry[0][3] += mx.m_entry[0][3];
    m_entry[1][0] += mx.m_entry[1][0];
    m_entry[1][1] += mx.m_entry[1][1];
    m_entry[1][2] += mx.m_entry[1][2];
    m_entry[1][3] += mx.m_entry[1][3];
    m_entry[2][0] += mx.m_entry[2][0];
    m_entry[2][1] += mx.m_entry[2][1];
    m_entry[2][2] += mx.m_entry[2][2];
    m_entry[2][3] += mx.m_entry[2][3];
    m_entry[3][0] += mx.m_entry[3][0];
    m_entry[3][1] += mx.m_entry[3][1];
    m_entry[3][2] += mx.m_entry[3][2];
    m_entry[3][3] += mx.m_entry[3][3];
    return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& mx)
{
    m_entry[0][0] -= mx.m_entry[0][0];
    m_entry[0][1] -= mx.m_entry[0][1];
    m_entry[0][2] -= mx.m_entry[0][2];
    m_entry[0][3] -= mx.m_entry[0][3];
    m_entry[1][0] -= mx.m_entry[1][0];
    m_entry[1][1] -= mx.m_entry[1][1];
    m_entry[1][2] -= mx.m_entry[1][2];
    m_entry[1][3] -= mx.m_entry[1][3];
    m_entry[2][0] -= mx.m_entry[2][0];
    m_entry[2][1] -= mx.m_entry[2][1];
    m_entry[2][2] -= mx.m_entry[2][2];
    m_entry[2][3] -= mx.m_entry[2][3];
    m_entry[3][0] -= mx.m_entry[3][0];
    m_entry[3][1] -= mx.m_entry[3][1];
    m_entry[3][2] -= mx.m_entry[3][2];
    m_entry[3][3] -= mx.m_entry[3][3];
    return *this;
}

Matrix4& Matrix4::operator*=(float scalar)
{
    m_entry[0][0] *= scalar;
    m_entry[0][1] *= scalar;
    m_entry[0][2] *= scalar;
    m_entry[0][3] *= scalar;
    m_entry[1][0] *= scalar;
    m_entry[1][1] *= scalar;
    m_entry[1][2] *= scalar;
    m_entry[1][3] *= scalar;
    m_entry[2][0] *= scalar;
    m_entry[2][1] *= scalar;
    m_entry[2][2] *= scalar;
    m_entry[2][3] *= scalar;
    m_entry[3][0] *= scalar;
    m_entry[3][1] *= scalar;
    m_entry[3][2] *= scalar;
    m_entry[3][3] *= scalar;
    return *this;
}

Matrix4& Matrix4::operator/=(float scalar)
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    const float inv = 1.0f / scalar;
    m_entry[0][0] *= inv;
    m_entry[0][1] *= inv;
    m_entry[0][2] *= inv;
    m_entry[0][3] *= inv;
    m_entry[1][0] *= inv;
    m_entry[1][1] *= inv;
    m_entry[1][2] *= inv;
    m_entry[1][3] *= inv;
    m_entry[2][0] *= inv;
    m_entry[2][1] *= inv;
    m_entry[2][2] *= inv;
    m_entry[2][3] *= inv;
    m_entry[3][0] *= inv;
    m_entry[3][1] *= inv;
    m_entry[3][2] *= inv;
    m_entry[3][3] *= inv;
    return *this;
}

Vector4 Matrix4::operator*(const Vector4& v) const
{
    return { m_entry[0][0] * v.x() + m_entry[0][1] * v.y() + m_entry[0][2] * v.z() + m_entry[0][3] * v.w(),
        m_entry[1][0] * v.x() + m_entry[1][1] * v.y() + m_entry[1][2] * v.z() + m_entry[1][3] * v.w(),
        m_entry[2][0] * v.x() + m_entry[2][1] * v.y() + m_entry[2][2] * v.z() + m_entry[2][3] * v.w(),
        m_entry[3][0] * v.x() + m_entry[3][1] * v.y() + m_entry[3][2] * v.z() + m_entry[3][3] * v.w() };
}

Point3 Matrix4::operator*(const Point3& p) const
{
    const float inv_w = 1.0f / (m_entry[3][0] * p.x() + m_entry[3][1] * p.y() + m_entry[3][2] * p.z() + m_entry[3][3]);
    return { (m_entry[0][0] * p.x() + m_entry[0][1] * p.y() + m_entry[0][2] * p.z() + m_entry[0][3]) * inv_w,
        (m_entry[1][0] * p.x() + m_entry[1][1] * p.y() + m_entry[1][2] * p.z() + m_entry[1][3]) * inv_w,
        (m_entry[2][0] * p.x() + m_entry[2][1] * p.y() + m_entry[2][2] * p.z() + m_entry[2][3]) * inv_w };
}

Vector3 Matrix4::operator*(const Vector3& v) const
{
    return { m_entry[0][0] * v.x() + m_entry[0][1] * v.y() + m_entry[0][2] * v.z(),
        m_entry[1][0] * v.x() + m_entry[1][1] * v.y() + m_entry[1][2] * v.z(),
        m_entry[2][0] * v.x() + m_entry[2][1] * v.y() + m_entry[2][2] * v.z() };
}

Matrix4 Matrix4::transpose() const
{
    return { m_entry[0][0], m_entry[1][0], m_entry[2][0], m_entry[3][0],
        m_entry[0][1], m_entry[1][1], m_entry[2][1], m_entry[3][1],
        m_entry[0][2], m_entry[1][2], m_entry[2][2], m_entry[3][2],
        m_entry[0][3], m_entry[1][3], m_entry[2][3], m_entry[3][3] };
}

Matrix4 Matrix4::inverse() const
{
    const float det = determinant();
    assert(!FloatCompare::isEqual(det, 0.0f));
    const float inv_det = 1.0f / det;
    return adjoint() * inv_det;
}

Matrix4 Matrix4::adjoint() const
{
    return { minorDeterminant(1, 2, 3, 1, 2, 3),
        -minorDeterminant(0, 2, 3, 1, 2, 3),
        minorDeterminant(0, 1, 3, 1, 2, 3),
        -minorDeterminant(0, 1, 2, 1, 2, 3),

        -minorDeterminant(1, 2, 3, 0, 2, 3),
        minorDeterminant(0, 2, 3, 0, 2, 3),
        -minorDeterminant(0, 1, 3, 0, 2, 3),
        minorDeterminant(0, 1, 2, 0, 2, 3),

        minorDeterminant(1, 2, 3, 0, 1, 3),
        -minorDeterminant(0, 2, 3, 0, 1, 3),
        minorDeterminant(0, 1, 3, 0, 1, 3),
        -minorDeterminant(0, 1, 2, 0, 1, 3),

        -minorDeterminant(1, 2, 3, 0, 1, 2),
        minorDeterminant(0, 2, 3, 0, 1, 2),
        -minorDeterminant(0, 1, 3, 0, 1, 2),
        minorDeterminant(0, 1, 2, 0, 1, 2) };
}

float Matrix4::determinant() const
{
    return m_entry[0][0] * minorDeterminant(1, 2, 3, 1, 2, 3) -
        m_entry[0][1] * minorDeterminant(1, 2, 3, 0, 2, 3) +
        m_entry[0][2] * minorDeterminant(1, 2, 3, 0, 1, 3) -
        m_entry[0][3] * minorDeterminant(1, 2, 3, 0, 1, 2);
}

float Matrix4::minorDeterminant(unsigned r0, unsigned r1, unsigned r2, unsigned c0, unsigned c1, unsigned c2) const
{
    assert(r0 <= 3);
    assert(r1 <= 3);
    assert(r2 <= 3);
    assert(c0 <= 3);
    assert(c1 <= 3);
    assert(c2 <= 3);
    return m_entry[r0][c0] * (m_entry[r1][c1] * m_entry[r2][c2] - m_entry[r2][c1] * m_entry[r1][c2]) -
        m_entry[r0][c1] * (m_entry[r1][c0] * m_entry[r2][c2] - m_entry[r2][c0] * m_entry[r1][c2]) +
        m_entry[r0][c2] * (m_entry[r1][c0] * m_entry[r2][c1] - m_entry[r2][c0] * m_entry[r1][c1]);
};

const Matrix4 Matrix4::ZERO = Matrix4::makeZero();
const Matrix4 Matrix4::IDENTITY = Matrix4::makeIdentity();

Matrix4 Matrix4::makeTranslateTransform(float tx, float ty, float tz)
{
    return { 1.0f, 0.0f, 0.0f, tx,
        0.0f, 1.0f, 0.0f, ty,
        0.0f, 0.0f, 1.0f, tz,
        0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4 Matrix4::makeTranslateTransform(const Vector3& vec)
{
    return { 1.0f, 0.0f, 0.0f, vec.x(),
        0.0f, 1.0f, 0.0f, vec.y(),
        0.0f, 0.0f, 1.0f, vec.z(),
        0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4 Matrix4::makeScaleTransform(const Vector3& vec)
{
    return { vec.x(), 0.0f, 0.0f, 0.0f,
        0.0f, vec.y(), 0.0f, 0.0f,
        0.0f, 0.0f, vec.z(), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4 Matrix4::makeScaleTransform(float sx, float sy, float sz)
{
    return { sx, 0.0f, 0.0f, 0.0f,
        0.0f, sy, 0.0f, 0.0f,
        0.0f, 0.0f, sz, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4 Matrix4::makeRotationXTransform(const Radian& radian)
{
    const float c = std::cos(radian.value());
    const float s = std::sin(radian.value());
    return { 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, c, -s, 0.0f,
        0.0f, s, c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4 Matrix4::makeRotationYTransform(const Radian& radian)
{
    const float c = std::cos(radian.value());
    const float s = std::sin(radian.value());
    return { c, 0.0f, s, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -s, 0.0f, c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4 Matrix4::makeRotationZTransform(const Radian& radian)
{
    const float c = std::cos(radian.value());
    const float s = std::sin(radian.value());
    return { c, -s, 0.0f, 0.0f,
        s, c, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4 Matrix4::makeRotationYawPitchRoll(const Radian& yaw, const Radian& pitch, const Radian& roll)
{
    return makeRotationYTransform(yaw) * makeRotationXTransform(pitch) * makeRotationZTransform(roll);
}

Matrix4 Matrix4::fromScaleRotationTranslate(const Vector3& scale, const Matrix3& rot, const Vector3& trans)
{
    return { scale.x() * rot[0][0], scale.y() * rot[0][1], scale.z() * rot[0][2], trans.x(),
        scale.x() * rot[1][0], scale.y() * rot[1][1], scale.z() * rot[1][2], trans.y(),
        scale.x() * rot[2][0], scale.y() * rot[2][1], scale.z() * rot[2][2], trans.z(),
        0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4 Matrix4::fromScaleQuaternionTranslate(const Vector3& scale, const Quaternion& rot, const Vector3& trans)
{
    Matrix4 rm = Matrix4::IDENTITY;
    const float x = rot.x();
    const float y = rot.y();
    const float z = rot.z();
    const float w = rot.w();

    const float tx = 2.0f * x;
    const float ty = 2.0f * y;
    const float tz = 2.0f * z;
    const float twx = tx * w;
    const float twy = ty * w;
    const float twz = tz * w;
    const float txx = tx * x;
    const float txy = ty * x;
    const float txz = tz * x;
    const float tyy = ty * y;
    const float tyz = tz * y;
    const float tzz = tz * z;

    rm[0][0] = scale.x() * (1.0f - (tyy + tzz));
    rm[0][1] = scale.y() * (txy - twz);
    rm[0][2] = scale.z() * (txz + twy);
    rm[0][3] = trans.x();
    rm[1][0] = scale.x() * (txy + twz);
    rm[1][1] = scale.y() * (1.0f - (txx + tzz));
    rm[1][2] = scale.z() * (tyz - twx);
    rm[1][3] = trans.y();
    rm[2][0] = scale.x() * (txz - twy);
    rm[2][1] = scale.y() * (tyz + twx);
    rm[2][2] = scale.z() * (1.0f - (txx + tyy));
    rm[2][3] = trans.z();

    return rm;
}

Point3 Matrix4::extractTranslation() const
{
    return { m_entry[0][3], m_entry[1][3], m_entry[2][3] };
}

Vector3 Matrix4::extractScale() const
{
    Vector3 s;
    const Vector3 v0{ m_entry[0][0], m_entry[1][0], m_entry[2][0] };
    const Vector3 v1{ m_entry[0][1], m_entry[1][1], m_entry[2][1] };
    const Vector3 v2{ m_entry[0][2], m_entry[1][2], m_entry[2][2] };
    s.x(v0.length());
    s.y(v1.length());
    s.z(v2.length());
    if (const Vector3 nor = v0.cross(v1); nor.dot(v2) < 0.0f)
    {
        // 有-1的scale, 但是不知道是哪個軸, 用eigen找mirror plane
        EigenDecompose<Matrix3> eigen = eigenDecomposition(Matrix3(*this));
        if (FloatCompare::isEqual(eigen.m_diag[0][0], -1.0f)) // eigen value有排序，第一個應該就是-1
        {
            // 不多做計算了，最大的那個軸就抓出來反向
            const Vector3 axis{ std::fabs(eigen.m_rot[0][0]), std::fabs(eigen.m_rot[1][0]), std::fabs(eigen.m_rot[2][0]) };
            if ((axis.x() > axis.y()) && (axis.x() > axis.z()))
            {
                s.x(-1.0f * s.x());
            }
            else if ((axis.y() > axis.x()) && (axis.y() > axis.z()))
            {
                s.y(-1.0f * s.y());
            }
            else
            {
                s.z(-1.0f * s.z());
            }
        }
    }
    return s;
}

Matrix3 Matrix4::extractRotation() const
{
    Matrix3 r;
    const Vector3 s = extractScale();
    r[0][0] = m_entry[0][0] / s.x();
    r[1][0] = m_entry[1][0] / s.x();
    r[2][0] = m_entry[2][0] / s.x();
    r[0][1] = m_entry[0][1] / s.y();
    r[1][1] = m_entry[1][1] / s.y();
    r[2][1] = m_entry[2][1] / s.y();
    r[0][2] = m_entry[0][2] / s.z();
    r[1][2] = m_entry[1][2] / s.z();
    r[2][2] = m_entry[2][2] / s.z();
    return r;
}

std::tuple<Vector3, Matrix3, Point3> Matrix4::unmatrixScaleRotateMatrixTranslation() const
{
    return { extractScale(), extractRotation(), extractTranslation() };
}

std::tuple<Vector3, Quaternion, Point3> Matrix4::unmatrixScaleQuaternionTranslation() const
{
    auto [s, r, t] = unmatrixScaleRotateMatrixTranslation();
    const Quaternion rot = Quaternion::fromRotationMatrix(r);
    return { s, rot, t };
}

float Matrix4::getMaxScale() const
{
    const Vector3 s = extractScale();
    return std::max({ std::abs(s.x()), std::abs(s.y()), std::abs(s.z()) });
}

namespace Math
{
    Matrix4 operator*(float scalar, const Matrix4& mx)
    {
        return mx * scalar;
    }
}
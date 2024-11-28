#include "Vector3.hpp"
#include "Vector4.hpp"
#include "MathGlobal.hpp"
#include <cassert>
#include <cmath>

using namespace Math;

Vector3::Vector3() : m_x(0.0f), m_y(0.0f), m_z(0.0f)
{
}

Vector3::Vector3(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
{
}

Vector3::Vector3(const std::array<float, 3>& f) : m_x(f[0]), m_y(f[1]), m_z(f[2])
{
}

Vector3::operator const float* () const
{
    return &m_x;
}

Vector3::operator float* ()
{
    return &m_x;
}

float Vector3::x() const
{
    return m_x;
}

void Vector3::x(float x)
{
    m_x = x;
}

float Vector3::y() const
{
    return m_y;
}

void Vector3::y(float y)
{
    m_y = y;
}

float Vector3::z() const
{
    return m_z;
}

void Vector3::z(float z)
{
    m_z = z;
}

Vector3& Vector3::operator= (const Vector4& v)
{
    m_x = v.x();
    m_y = v.y();
    m_z = v.z();
    return *this;
}

bool Vector3::operator== (const Vector3& v) const
{
    return FloatCompare::isEqual(m_x, v.m_x) && FloatCompare::isEqual(m_y, v.m_y) && FloatCompare::isEqual(m_z, v.m_z);
}

bool Vector3::operator!= (const Vector3& v) const
{
    return !FloatCompare::isEqual(m_x, v.m_x) || !FloatCompare::isEqual(m_y, v.m_y) || !FloatCompare::isEqual(m_z, v.m_z);
}

Vector3 Vector3::operator+ (const Vector3& v) const
{
    return Vector3{ m_x + v.m_x, m_y + v.m_y, m_z + v.m_z };
}

Vector3 Vector3::operator- (const Vector3& v) const
{
    return Vector3{ m_x - v.m_x, m_y - v.m_y, m_z - v.m_z };
}

Vector3 Vector3::operator* (float scalar) const
{
    return Vector3{ m_x * scalar, m_y * scalar, m_z * scalar };
}

Vector3 Vector3::operator/ (float scalar) const
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    return Vector3{ m_x / scalar, m_y / scalar, m_z / scalar };
}

Vector3 Vector3::operator- () const
{
    return Vector3{ -m_x, -m_y, -m_z };
}

Vector3& Vector3::operator+= (const Vector3& v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
    return *this;
}

Vector3& Vector3::operator-= (const Vector3& v)
{
    m_x -= v.m_x;
    m_y -= v.m_y;
    m_z -= v.m_z;
    return *this;
}

Vector3& Vector3::operator*= (float scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    return *this;
}

Vector3& Vector3::operator/= (float scalar)
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    return *this;
}

float Vector3::length() const
{
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

float Vector3::squaredLength() const
{
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

float Vector3::dot(const Vector3& v) const
{
    return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z;
}

void Vector3::normalizeSelf()
{
    const float len = length();
    assert(!FloatCompare::isEqual(len, 0.0f));
    m_x /= len;
    m_y /= len;
    m_z /= len;
}

Vector3 Vector3::normalize() const
{
    const float len = length();
    assert(!FloatCompare::isEqual(len, 0.0f));
    return Vector3{ m_x / len, m_y / len, m_z / len };
}

void Vector3::homogenizeSelf()
{
    assert(!FloatCompare::isEqual(m_z, 0.0f));
    m_x /= m_z;
    m_y /= m_z;
    m_z = 1.0f;
}

Vector3 Vector3::homogenize() const
{
    assert(!FloatCompare::isEqual(m_z, 0.0f));
    return Vector3{ m_x / m_z, m_y / m_z, 1.0f };
}

Vector3 Vector3::cross(const Vector3& v) const
{
    return Vector3{ m_y * v.m_z - m_z * v.m_y, m_z * v.m_x - m_x * v.m_z, m_x * v.m_y - m_y * v.m_x };
}

Vector3 Vector3::unitCross(const Vector3& v) const
{
    return cross(v).normalize();
}

const Vector3 Vector3::ZERO{ 0.0f, 0.0f, 0.0f };
const Vector3 Vector3::UNIT_X{ 1.0f, 0.0f, 0.0f };
const Vector3 Vector3::UNIT_Y{ 0.0f, 1.0f, 0.0f };
const Vector3 Vector3::UNIT_Z{ 0.0f, 0.0f, 1.0f };

namespace Math
{
    Vector3 operator* (float scalar, const Vector3& v)
    {
        return v * scalar;
    }
}
#include "Vector4.hpp"
#include "MathGlobal.hpp"
#include "Vector3.hpp"
#include <cassert>
#include <cmath>

using namespace Math;

Vector4::Vector4() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f)
{
}

Vector4::Vector4(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w)
{
}

Vector4::Vector4(const Vector3& vec, float w) : m_x(vec.x()), m_y(vec.y()), m_z(vec.z()), m_w(w)
{
}

Vector4::Vector4(const std::array<float, 4>& f) : m_x(f[0]), m_y(f[1]), m_z(f[2]), m_w(f[3])
{
}

Vector4::operator const float* () const
{
    return &m_x;
}

Vector4::operator float* ()
{
    return &m_x;
}

float Vector4::x() const
{
    return m_x;
}

void Vector4::x(float x)
{
    m_x = x;
}

float Vector4::y() const
{
    return m_y;
}

void Vector4::y(float y)
{
    m_y = y;
}

float Vector4::z() const
{
    return m_z;
}

void Vector4::z(float z)
{
    m_z = z;
}

float Vector4::w() const
{
    return m_w;
}

void Vector4::w(float w)
{
    m_w = w;
}

bool Vector4::operator== (const Vector4& v) const
{
    return FloatCompare::isEqual(m_x, v.m_x) && FloatCompare::isEqual(m_y, v.m_y) && FloatCompare::isEqual(m_z, v.m_z) && FloatCompare::isEqual(m_w, v.m_w);
}

bool Vector4::operator!= (const Vector4& v) const
{
    return !FloatCompare::isEqual(m_x, v.m_x) || !FloatCompare::isEqual(m_y, v.m_y) || !FloatCompare::isEqual(m_z, v.m_z) || !FloatCompare::isEqual(m_w, v.m_w);
}

Vector4 Vector4::operator+ (const Vector4& v) const
{
    return Vector4{ m_x + v.m_x, m_y + v.m_y, m_z + v.m_z, m_w + v.m_w };
}

Vector4 Vector4::operator- (const Vector4& v) const
{
    return Vector4{ m_x - v.m_x, m_y - v.m_y, m_z - v.m_z, m_w - v.m_w };
}

Vector4 Vector4::operator* (float scalar) const
{
    return Vector4{ m_x * scalar, m_y * scalar, m_z * scalar, m_w * scalar };
}

Vector4 Vector4::operator/ (float scalar) const
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    return Vector4{ m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar };
}

Vector4 Vector4::operator- () const
{
    return Vector4{ -m_x, -m_y, -m_z, -m_w };
}

Vector4& Vector4::operator+= (const Vector4& v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
    m_w += v.m_w;
    return *this;
}

Vector4& Vector4::operator-= (const Vector4& v)
{
    m_x -= v.m_x;
    m_y -= v.m_y;
    m_z -= v.m_z;
    m_w -= v.m_w;
    return *this;
}

Vector4& Vector4::operator*= (float scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    m_w *= scalar;
    return *this;
}

Vector4& Vector4::operator/= (float scalar)
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    m_w /= scalar;
    return *this;
}

float Vector4::length() const
{
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

float Vector4::squaredLength() const
{
    return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
}

float Vector4::dot(const Vector4& v) const
{
    return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z + m_w * v.m_w;
}

void Vector4::normalizeSelf()
{
    const float len = length();
    assert(!FloatCompare::isEqual(len, 0.0f));
    m_x /= len;
    m_y /= len;
    m_z /= len;
    m_w /= len;
}

Vector4 Vector4::normalize() const
{
    const float len = length();
    assert(!FloatCompare::isEqual(len, 0.0f));
    return Vector4{ m_x / len, m_y / len, m_z / len, m_w / len };
}

const Vector4 Vector4::ZERO{ 0.0f, 0.0f, 0.0f, 0.0f };
const Vector4 Vector4::UNIT_X{ 1.0f, 0.0f, 0.0f, 0.0f };
const Vector4 Vector4::UNIT_Y{ 0.0f, 1.0f, 0.0f, 0.0f };
const Vector4 Vector4::UNIT_Z{ 0.0f, 0.0f, 1.0f, 0.0f };
const Vector4 Vector4::UNIT_W{ 0.0f, 0.0f, 0.0f, 1.0f };

namespace Math
{
    Vector4 operator* (float scalar, const Vector4& v)
    {
        return v * scalar;
    }
}
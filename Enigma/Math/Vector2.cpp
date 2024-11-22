#include "Vector2.hpp"
#include "MathGlobal.hpp"
#include <cassert>
#include <cmath>

using namespace Math;

Vector2::Vector2() : m_x(0.0f), m_y(0.0f)
{
}

Vector2::Vector2(float x, float y) : m_x(x), m_y(y)
{
}

Vector2::Vector2(const std::array<float, 2>& f) : m_x(f[0]), m_y(f[1])
{
}

Vector2::operator const float* () const
{
    return &m_x;
}

Vector2::operator float* ()
{
    return &m_x;
}

float Vector2::x() const
{
    return m_x;
}

void Vector2::x(float x)
{
    m_x = x;
}

float Vector2::y() const
{
    return m_y;
}

void Vector2::y(float y)
{
    m_y = y;
}

bool Vector2::operator== (const Vector2& v) const
{
    return FloatCompare::isEqual(m_x, v.m_x) && FloatCompare::isEqual(m_y, v.m_y);
}

bool Vector2::operator!= (const Vector2& v) const
{
    return !FloatCompare::isEqual(m_x, v.m_x) || !FloatCompare::isEqual(m_y, v.m_y);
}

Vector2 Vector2::operator+ (const Vector2& v) const
{
    return Vector2{ m_x + v.m_x, m_y + v.m_y };
}

Vector2 Vector2::operator- (const Vector2& v) const
{
    return Vector2{ m_x - v.m_x, m_y - v.m_y };
}

Vector2 Vector2::operator* (float scalar) const
{
    return Vector2{ m_x * scalar, m_y * scalar };
}

Vector2 Vector2::operator/ (float scalar) const
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    return Vector2{ m_x / scalar, m_y / scalar };
}

Vector2 Vector2::operator- () const
{
    return Vector2{ -m_x, -m_y };
}

Vector2& Vector2::operator+= (const Vector2& v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    return *this;
}

Vector2& Vector2::operator-= (const Vector2& v)
{
    m_x -= v.m_x;
    m_y -= v.m_y;
    return *this;
}

Vector2& Vector2::operator*= (float scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    return *this;
}

Vector2& Vector2::operator/= (float scalar)
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    m_x /= scalar;
    m_y /= scalar;
    return *this;
}

float Vector2::length() const
{
    return std::sqrt(m_x * m_x + m_y * m_y);
}

float Vector2::squaredLength() const
{
    return m_x * m_x + m_y * m_y;
}

float Vector2::dot(const Vector2& v) const
{
    return m_x * v.m_x + m_y * v.m_y;
}

Vector2 Vector2::normalize() const
{
    const float len = length();
    assert(!FloatCompare::isEqual(len, 0.0f));
    return Vector2{ m_x / len, m_y / len };
}

void Vector2::normalizeSelf()
{
    const float len = length();
    assert(!FloatCompare::isEqual(len, 0.0f));
    m_x /= len;
    m_y /= len;
}

Vector2 Vector2::perp() const
{
    return Vector2{ m_y, -m_x };
}

Vector2 Vector2::unitPerp() const
{
    const float len = length();
    assert(!FloatCompare::isEqual(len, 0.0f));
    return Vector2{ m_y / len, -m_x / len };
}

float Vector2::dotPerp(const Vector2& v) const
{
    return m_x * v.m_y - m_y * v.m_x;
}

const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::UNIT_X(1.0f, 0.0f);
const Vector2 Vector2::UNIT_Y(0.0f, 1.0f);

namespace Math
{
    Vector2 operator* (float scalar, const Vector2& v)
    {
        return Vector2{ scalar * v.x(), scalar * v.y() };
    }
}
#include "Point2.hpp"
#include "Vector2.hpp"
#include "MathGlobal.hpp"
#include <cassert>

using namespace Math;

Point2::Point2() : m_x(0.0f), m_y(0.0f)
{
}

Point2::Point2(float x, float y) : m_x(x), m_y(y)
{
}

bool Point2::operator==(const Point2& p) const
{
    return FloatCompare::isEqual(m_x, p.m_x) && FloatCompare::isEqual(m_y, p.m_y);
}

bool Point2::operator!=(const Point2& p) const
{
    return !(*this == p);
}

float Point2::x() const
{
    return m_x;
}

void Point2::x(float x)
{
    m_x = x;
}

float Point2::y() const
{
    return m_y;
}

void Point2::y(float y)
{
    m_y = y;
}

Point2 Point2::operator+(const Point2& p) const
{
    return { m_x + p.m_x, m_y + p.m_y };
}

Point2 Point2::operator+(const Vector2& v) const
{
    return { m_x + v.x(), m_y + v.y() };
}

Vector2 Point2::operator-(const Point2& p) const
{
    return { m_x - p.m_x, m_y - p.m_y };
}

Point2 Point2::operator*(float scalar) const
{
    return { m_x * scalar, m_y * scalar };
}

Point2 Point2::operator/(float scalar) const
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    const float inv = 1.0f / scalar;
    return { m_x * inv, m_y * inv };
}

Point2 Point2::operator-() const
{
    return { -m_x, -m_y };
}

Point2& Point2::operator+=(const Point2& p)
{
    m_x += p.m_x;
    m_y += p.m_y;
    return *this;
}

Point2& Point2::operator+=(const Vector2& v)
{
    m_x += v.x();
    m_y += v.y();
    return *this;
}

namespace Math
{
    Point2 operator* (float scalar, const Point2& p)
    {
        return Point2{ scalar * p.x(), scalar * p.y() };
    }
}

const Point2 Point2::ZERO = Point2(0.0f, 0.0f);

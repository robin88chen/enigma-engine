#include "Point3.hpp"
#include "Vector3.hpp"
#include "MathGlobal.hpp"
#include <cassert>

using namespace Math;

Point3::Point3() : m_x(0.0f), m_y(0.0f), m_z(0.0f)
{
}

Point3::Point3(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
{
}

bool Point3::operator==(const Point3& p) const
{
    return FloatCompare::isEqual(m_x, p.m_x) && FloatCompare::isEqual(m_y, p.m_y) && FloatCompare::isEqual(m_z, p.m_z);
}

bool Point3::operator!=(const Point3& p) const
{
    return !(*this == p);
}

float Point3::x() const
{
    return m_x;
}

void Point3::x(float x)
{
    m_x = x;
}

float Point3::y() const
{
    return m_y;
}

void Point3::y(float y)
{
    m_y = y;
}

float Point3::z() const
{
    return m_z;
}

void Point3::z(float z)
{
    m_z = z;
}

Point3 Point3::operator+(const Point3& p) const
{
    return { m_x + p.m_x, m_y + p.m_y, m_z + p.m_z };
}

Point3 Point3::operator+(const Vector3& v) const
{
    return { m_x + v.x(), m_y + v.y(), m_z + v.z() };
}

Vector3 Point3::operator-(const Point3& p) const
{
    return { m_x - p.m_x, m_y - p.m_y, m_z - p.m_z };
}

Point3 Point3::operator*(float scalar) const
{
    return { m_x * scalar, m_y * scalar, m_z * scalar };
}

Point3 Point3::operator/(float scalar) const
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    const float inv_scalar = 1.0f / scalar;
    return { m_x * inv_scalar, m_y * inv_scalar, m_z * inv_scalar };
}

Point3 Point3::operator-() const
{
    return { -m_x, -m_y, -m_z };
}

Point3& Point3::operator+=(const Point3& p)
{
    m_x += p.m_x;
    m_y += p.m_y;
    m_z += p.m_z;
    return *this;
}

Point3& Point3::operator+=(const Vector3& v)
{
    m_x += v.x();
    m_y += v.y();
    m_z += v.z();
    return *this;
}

namespace Math
{
    Point3 operator* (float scalar, const Point3& p)
    {
        return Point3{ scalar * p.x(), scalar * p.y(), scalar * p.z() };
    }
}

const Point3 Point3::ZERO = Point3(0.0f, 0.0f, 0.0f);
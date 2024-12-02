#include "Line3.hpp"
#include <cassert>

using namespace Math;

Line3::Line3() : m_origin(Vector3::ZERO), m_direction(Vector3::UNIT_X)
{
}

Line3::Line3(const Vector3& origin, const Vector3& direction) : m_origin(origin), m_direction(direction)
{
    assert(m_direction.isUnitLength());
}

Vector3 Line3::origin() const
{
    return m_origin;
}

void Line3::origin(const Vector3& origin)
{
    m_origin = origin;
}

Vector3 Line3::direction() const
{
    return m_direction;
}

void Line3::direction(const Vector3& direction)
{
    assert(direction.isUnitLength());
    m_direction = direction;
}

bool Line3::operator== (const Line3& line) const
{
    return m_origin == line.m_origin && m_direction == line.m_direction;
}

bool Line3::operator!= (const Line3& line) const
{
    return m_origin != line.m_origin || m_direction != line.m_direction;
}

#include "Line2.hpp"
#include <cassert>

using namespace Math;

Line2::Line2() : m_origin(Vector2::ZERO), m_direction(Vector2::UNIT_X)
{
}

Line2::Line2(const Vector2& origin, const Vector2& direction) : m_origin(origin), m_direction(direction)
{
    assert(m_direction.isUnitLength());
}

Vector2 Line2::origin() const
{
    return m_origin;
}

void Line2::origin(const Vector2& origin)
{
    m_origin = origin;
}

Vector2 Line2::direction() const
{
    return m_direction;
}

void Line2::direction(const Vector2& direction)
{
    assert(direction.isUnitLength());
    m_direction = direction;
}

bool Line2::operator== (const Line2& line) const
{
    return m_origin == line.m_origin && m_direction == line.m_direction;
}

bool Line2::operator!= (const Line2& line) const
{
    return m_origin != line.m_origin || m_direction != line.m_direction;
}

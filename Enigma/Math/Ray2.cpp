#include "Ray2.hpp"
#include <cassert>

using namespace Math;

Ray2::Ray2() : m_origin(Vector2::ZERO), m_direction(Vector2::UNIT_X)
{
}

Ray2::Ray2(const Vector2& origin, const Vector2& direction) : m_origin(origin), m_direction(direction)
{
    assert(m_direction.isUnitLength());
}

Vector2 Ray2::origin() const
{
    return m_origin;
}

void Ray2::origin(const Vector2& origin)
{
    m_origin = origin;
}

Vector2 Ray2::direction() const
{
    return m_direction;
}

void Ray2::direction(const Vector2& direction)
{
    assert(direction.isUnitLength());
    m_direction = direction;
}

bool Ray2::operator== (const Ray2& ray) const
{
    return m_origin == ray.m_origin && m_direction == ray.m_direction;
}

bool Ray2::operator!= (const Ray2& ray) const
{
    return m_origin != ray.m_origin || m_direction != ray.m_direction;
}

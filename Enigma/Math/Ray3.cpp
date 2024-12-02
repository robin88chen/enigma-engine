#include "Ray3.hpp"
#include <cassert>

using namespace Math;

Ray3::Ray3() : m_origin(Vector3::ZERO), m_direction(Vector3::UNIT_Z)
{
}

Ray3::Ray3(const Vector3& origin, const Vector3& direction) : m_origin(origin), m_direction(direction)
{
    assert(m_direction.isUnitLength());
}

Vector3 Ray3::origin() const
{
    return m_origin;
}

void Ray3::origin(const Vector3& origin)
{
    m_origin = origin;
}

Vector3 Ray3::direction() const
{
    return m_direction;
}

void Ray3::direction(const Vector3& direction)
{
    assert(direction.isUnitLength());
    m_direction = direction;
}

bool Ray3::operator== (const Ray3& ray) const
{
    return m_origin == ray.m_origin && m_direction == ray.m_direction;
}

bool Ray3::operator!= (const Ray3& ray) const
{
    return m_origin != ray.m_origin || m_direction != ray.m_direction;
}

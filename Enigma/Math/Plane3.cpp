#include "Plane3.hpp"
#include "MathGlobal.hpp"
#include <cassert>

using namespace Math;

Plane3::Plane3() : m_normal(Vector3::UNIT_Z), m_constant(0.0f)
{
}

Plane3::Plane3(const Vector3& normal, float constant) : m_normal(normal), m_constant(constant)
{
    assert(m_normal.isUnitLength());
}

Plane3::Plane3(const Vector3& normal, const Vector3& p) : m_normal(normal), m_constant(m_normal.dot(p))
{
    assert(m_normal.isUnitLength());
}

Plane3::Plane3(const Vector3& p0, const Vector3& p1, const Vector3& p2)
{
    m_normal = (p1 - p0).cross(p2 - p0);
    assert(!m_normal.isZero());
    m_normal.normalizeSelf();
    m_constant = m_normal.dot(p0);
}

Vector3 Plane3::normal() const
{
    return m_normal;
}

void Plane3::normal(const Vector3& normal)
{
    assert(normal.isUnitLength());
    m_normal = normal;
}

float Plane3::constant() const
{
    return m_constant;
}

void Plane3::constant(float c)
{
    m_constant = c;
}

bool Plane3::operator== (const Plane3& plane) const
{
    return m_normal == plane.m_normal && FloatCompare::isEqual(m_constant, plane.m_constant);
}

bool Plane3::operator!= (const Plane3& plane) const
{
    return m_normal != plane.m_normal || !FloatCompare::isEqual(m_constant, plane.m_constant);
}

Plane3::SideOfPlane Plane3::whichSide(const Vector3& p) const
{
    const float distance = m_normal.dot(p) - m_constant;
    if (distance > FloatCompare::ZERO_TOLERANCE)
    {
        return SideOfPlane::positive;
    }
    if (distance < -FloatCompare::ZERO_TOLERANCE)
    {
        return SideOfPlane::negative;
    }
    return SideOfPlane::overlap;
}

float Plane3::signedDistanceTo(const Vector3& q) const
{
    return m_normal.dot(q) - m_constant;
}

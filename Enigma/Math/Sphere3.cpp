#include "Sphere3.hpp"
#include "MathGlobal.hpp"
#include <cassert>

using namespace Math;

Sphere3::Sphere3() : m_center(Point3::ZERO), m_radius(0.0f)
{
}

Sphere3::Sphere3(const Point3& center, float radius) : m_center(center), m_radius(radius)
{
    assert(radius >= 0.0f);
}

Point3 Sphere3::center() const
{
    return m_center;
}

void Sphere3::center(const Point3& center)
{
    m_center = center;
}

float Sphere3::radius() const
{
    return m_radius;
}

void Sphere3::radius(float radius)
{
    assert(radius >= 0.0f);
    m_radius = radius;
}

bool Sphere3::operator== (const Sphere3& sphere) const
{
    return m_center == sphere.m_center && FloatCompare::isEqual(m_radius, sphere.m_radius);
}

bool Sphere3::operator!= (const Sphere3& sphere) const
{
    return m_center != sphere.m_center || !FloatCompare::isEqual(m_radius, sphere.m_radius);
}

bool Sphere3::isEmpty() const
{
    return m_radius <= 0.0f;
}

const Sphere3 Sphere3::UNIT_SPHERE(Point3{ 0.0f, 0.0f, 0.0f }, 1.0f);
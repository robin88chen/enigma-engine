#include "IntrRay3Plane3.hpp"
#include "Math/MathGlobal.hpp"
#include <cassert>

using namespace Collision;

IntrRay3Plane3::IntrRay3Plane3(const Math::Ray3& ray, const Math::Plane3& plane) : m_ray(ray), m_plane(plane), m_quantity(0), m_tParam(0.0f)
{
    m_intersectionType = IntersectionType::point;
}

const Math::Ray3& IntrRay3Plane3::ray() const
{
    return m_ray;
}

const Math::Plane3& IntrRay3Plane3::plane() const
{
    return m_plane;
}

bool IntrRay3Plane3::test()
{
    const float e = m_plane.normal().dot(m_ray.direction());
    if ((e <= Math::FloatCompare::zeroTolerance()) && (e >= -Math::FloatCompare::zeroTolerance())) return false;
    const float t = (m_plane.constant() - m_plane.normal().dot(m_ray.origin())) / e;
    if (t < 0.0f) return false;
    m_quantity = 1;
    m_tParam = t;
    m_point = t * m_ray.direction() + m_ray.origin();
    return true;
}

bool IntrRay3Plane3::find()
{
    return test();
}

unsigned IntrRay3Plane3::getQuantity() const
{
    return m_quantity;
}

const Math::Point3& IntrRay3Plane3::getPoint() const
{
    assert(m_quantity > 0);
    return m_point;
}

float IntrRay3Plane3::getRayT() const
{
    assert(m_quantity > 0);
    return m_tParam;
}

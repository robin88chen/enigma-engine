#include "IntrRay3Sphere3.hpp"
#include "Math/MathGlobal.hpp"
#include <cassert>
#include <cmath>

using namespace Collision;

IntrRay3Sphere3::IntrRay3Sphere3(const Math::Ray3& ray, const Math::Sphere3& sphere) : m_ray(ray), m_sphere(sphere), m_quantity(0), m_tParam{}
{
    m_intersectionType = IntersectionType::point;
}

const Math::Ray3& IntrRay3Sphere3::ray() const
{
    return m_ray;
}

const Math::Sphere3& IntrRay3Sphere3::sphere() const
{
    return m_sphere;
}

bool IntrRay3Sphere3::test()
{
    /** RaySphere intersection, form Real-time Rendering */
    const Math::Vector3 l = m_sphere.center() - m_ray.origin();
    const float s = l.dot(m_ray.direction());
    const float sq_l = l.squaredLength();
    const float sq_r = m_sphere.radius() * m_sphere.radius();
    if ((s < 0.0f) && (sq_l > sq_r + Math::FloatCompare::tolerance(sq_l, sq_r))) return false;

    if (const float sq_m = sq_l - s * s; sq_m > sq_r + Math::FloatCompare::tolerance(sq_m, sq_r)) return false;

    return true;
}

bool IntrRay3Sphere3::find()
{
    m_quantity = 0;
    /** RaySphere intersection, form Real-time Rendering */
    const Math::Vector3 l = m_sphere.center() - m_ray.origin();
    const float s = l.dot(m_ray.direction());
    const float sq_l = l.squaredLength();
    const float sq_r = m_sphere.radius() * m_sphere.radius();
    if ((s < 0.0f) && (sq_l > sq_r + Math::FloatCompare::tolerance(sq_l, sq_r))) return false;

    const float sq_m = sq_l - s * s;
    if (sq_m > sq_r + Math::FloatCompare::tolerance(sq_m, sq_r)) return false;

    const float q = std::sqrt(sq_r - sq_m);
    if (sq_l > sq_r)
    {
        m_quantity = 2;
        m_tParam[0] = s - q;
        m_tParam[1] = s + q;
        m_point[0] = m_tParam[0] * m_ray.direction() + m_ray.origin();
        m_point[1] = m_tParam[1] * m_ray.direction() + m_ray.origin();
    }
    else
    {
        m_quantity = 1;
        m_tParam[0] = s + q;
        m_point[0] = m_tParam[0] * m_ray.direction() + m_ray.origin();
    }
    return true;
}

unsigned IntrRay3Sphere3::getQuantity() const
{
    return m_quantity;
}

const Math::Point3& IntrRay3Sphere3::getPoint(unsigned i) const
{
    assert(i < m_quantity);
    return m_point[i];
}

float IntrRay3Sphere3::getRayT(unsigned i) const
{
    assert(i < m_quantity);
    return m_tParam[i];
}

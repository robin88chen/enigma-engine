#include "IntrRay3Triangle3.hpp"
#include "Math/MathGlobal.hpp"
#include <cassert>

using namespace Collision;

IntrRay3Triangle3::IntrRay3Triangle3(const Math::Ray3& ray, const Math::Triangle3& triangle) : m_ray(ray), m_triangle(triangle), m_quantity(0), m_tParam(0.0f)
{
    m_intersectionType = IntersectionType::point;
}

const Math::Ray3& IntrRay3Triangle3::ray() const
{
    return m_ray;
}

const Math::Triangle3& IntrRay3Triangle3::triangle() const
{
    return m_triangle;
}

bool IntrRay3Triangle3::test()
{
    const Math::Vector3 e1 = m_triangle.point(1) - m_triangle.point(0);
    const Math::Vector3 e2 = m_triangle.point(2) - m_triangle.point(0);
    const Math::Vector3 q = m_ray.direction().cross(e2);
    const float a = e1.dot(q);
    if ((a > -Math::FloatCompare::zeroTolerance()) && (a < Math::FloatCompare::zeroTolerance())) return false;
    const float f = 1.0f / a;
    const Math::Vector3 s = m_ray.origin() - m_triangle.point(0);
    const float u = f * (s.dot(q));
    if (u < 0.0f || u > 1.0f) return false;
    const Math::Vector3 r = s.cross(e1);
    const float v = f * (m_ray.direction().dot(r));
    if ((v < 0.0f) || (u + v > 1.0f)) return false;

    // if we got here, we found intersection
    const float t = f * (e2.dot(r));
    m_quantity = 1;
    m_tParam = t;
    m_point = t * m_ray.direction() + m_ray.origin();
    return true;
}

bool IntrRay3Triangle3::find()
{
    // 因為沒有多少運算上的差異，所以直接呼叫Test
    return test();
}

unsigned IntrRay3Triangle3::getQuantity() const
{
    return m_quantity;
}

const Math::Point3& IntrRay3Triangle3::getPoint() const
{
    assert(m_quantity > 0);
    return m_point;
}

float IntrRay3Triangle3::getRayT() const
{
    assert(m_quantity > 0);
    return m_tParam;
}
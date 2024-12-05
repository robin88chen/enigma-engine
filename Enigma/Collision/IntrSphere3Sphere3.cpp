#include "IntrSphere3Sphere3.hpp"

using namespace Collision;

IntrSphere3Sphere3::IntrSphere3Sphere3(const Math::Sphere3& sphere0, const Math::Sphere3& sphere1) : m_sphere0(sphere0), m_sphere1(sphere1)
{
}

const Math::Sphere3& IntrSphere3Sphere3::sphere0() const
{
    return m_sphere0;
}

const Math::Sphere3& IntrSphere3Sphere3::sphere1() const
{
    return m_sphere1;
}

bool IntrSphere3Sphere3::test()
{
    const Math::Vector3 center_diff = m_sphere1.center() - m_sphere0.center();
    const float sqr_distance = center_diff.squaredLength();
    const float sqr_radius_sum = (m_sphere0.radius() + m_sphere1.radius()) * (m_sphere0.radius() + m_sphere1.radius());
    return sqr_distance <= sqr_radius_sum;
}

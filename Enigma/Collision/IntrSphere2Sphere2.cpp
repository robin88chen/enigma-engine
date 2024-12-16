#include "IntrSphere2Sphere2.hpp"
#include "Math/Vector2.hpp"
#include "Math/MathGlobal.hpp"

using namespace Collision;

IntrSphere2Sphere2::IntrSphere2Sphere2(const Math::Sphere2& sphere0, const Math::Sphere2& sphere1) : m_sphere0(sphere0), m_sphere1(sphere1)
{
}

const Math::Sphere2& IntrSphere2Sphere2::sphere0() const
{
    return m_sphere0;
}

const Math::Sphere2& IntrSphere2Sphere2::sphere1() const
{
    return m_sphere1;
}

bool IntrSphere2Sphere2::test()
{
    const Math::Vector2 center_diff = m_sphere1.center() - m_sphere0.center();
    const float sqr_distance = center_diff.squaredLength();
    const float sqr_radius_sum = (m_sphere0.radius() + m_sphere1.radius()) * (m_sphere0.radius() + m_sphere1.radius());
    return sqr_distance <= sqr_radius_sum + Math::FloatCompare::tolerance(sqr_distance, sqr_radius_sum);
}

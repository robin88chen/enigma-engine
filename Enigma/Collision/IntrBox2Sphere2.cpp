#include "IntrBox2Sphere2.hpp"
#include <cmath>

using namespace Collision;

IntrBox2Sphere2::IntrBox2Sphere2(const Math::Box2& box, const Math::Sphere2& sphere) : m_box(box), m_sphere(sphere)
{
}

const Math::Box2& IntrBox2Sphere2::box() const
{
    return m_box;
}

const Math::Sphere2& IntrBox2Sphere2::sphere() const
{
    return m_sphere;
}

bool IntrBox2Sphere2::test()
{
    // Test for intersection in the coordinate system of the box by
    // transforming the sphere into that coordinate system.
    const Math::Vector2 center_diff = m_sphere.center() - m_box.center();

    const float ax = std::abs(center_diff.dot(m_box.axis(0)));
    const float ay = std::abs(center_diff.dot(m_box.axis(1)));
    const float dx = ax - m_box.extent(0);
    const float dy = ay - m_box.extent(1);

    return ((dx <= m_sphere.radius()) && (dy <= m_sphere.radius()));
}


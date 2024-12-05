#include "IntrBox3Sphere3.hpp"
#include <cmath>

using namespace Collision;

IntrBox3Sphere3::IntrBox3Sphere3(const Math::Box3& box, const Math::Sphere3& sphere) : m_box(box), m_sphere(sphere)
{
}

const Math::Box3& IntrBox3Sphere3::box() const
{
    return m_box;
}

const Math::Sphere3& IntrBox3Sphere3::sphere() const
{
    return m_sphere;
}

bool IntrBox3Sphere3::test()
{
    // Test for intersection in the coordinate system of the box by
    // transforming the sphere into that coordinate system.
    const Math::Vector3 center_diff = m_sphere.center() - m_box.center();

    const float ax = std::abs(center_diff.dot(m_box.axis(0)));
    const float ay = std::abs(center_diff.dot(m_box.axis(1)));
    const float az = std::abs(center_diff.dot(m_box.axis(2)));
    const float dx = ax - m_box.extent(0);
    const float dy = ay - m_box.extent(1);
    const float dz = az - m_box.extent(2);

    // NOLINTBEGIN(readability-else-after-return)
    if (ax <= m_box.extent(0))
    {
        if (ay <= m_box.extent(1))
        {
            if (az <= m_box.extent(2))
            {
                // sphere center inside box
                return true;
            }
            else
            {
                // potential sphere-face intersection with face z
                return dz <= m_sphere.radius();
            }
        }
        else
        {
            if (az <= m_box.extent(2))
            {
                // potential sphere-face intersection with face y
                return dy <= m_sphere.radius();
            }
            else
            {
                // potential sphere-edge intersection with edge formed
                // by faces y and z
                const float sqr_radius = m_sphere.radius() * m_sphere.radius();
                return dy * dy + dz * dz <= sqr_radius;
            }
        }
    }
    else
    {
        if (ay <= m_box.extent(1))
        {
            if (az <= m_box.extent(2))
            {
                // potential sphere-face intersection with face x
                return dx <= m_sphere.radius();
            }
            else
            {
                // potential sphere-edge intersection with edge formed
                // by faces x and z
                const float sqr_radius = m_sphere.radius() * m_sphere.radius();
                return dx * dx + dz * dz <= sqr_radius;
            }
        }
        else
        {
            if (az <= m_box.extent(2))
            {
                // potential sphere-edge intersection with edge formed
                // by faces x and y
                const float sqr_radius = m_sphere.radius() * m_sphere.radius();
                return dx * dx + dy * dy <= sqr_radius;
            }
            else
            {
                // potential sphere-vertex intersection at corner formed
                // by faces x,y,z
                const float sqr_radius = m_sphere.radius() * m_sphere.radius();
                return dx * dx + dy * dy + dz * dz <= sqr_radius;
            }
        }
    }
    // NOLINTEND(readability-else-after-return)
}


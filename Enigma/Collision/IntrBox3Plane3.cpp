#include "IntrBox3Plane3.hpp"
#include <cmath>
#include <array>

using namespace Collision;

IntrBox3Plane3::IntrBox3Plane3(const Math::Box3& box, const Math::Plane3& plane, bool is_aligned) : m_box(box), m_plane(plane), m_isAligned(is_aligned)
{
}

const Math::Box3& IntrBox3Plane3::box() const
{
    return m_box;
}

const Math::Plane3& IntrBox3Plane3::plane() const
{
    return m_plane;
}

bool IntrBox3Plane3::test()
{
    return (testPlaneSide() == Math::Plane3::SideOfPlane::overlap);
}

Math::Plane3::SideOfPlane IntrBox3Plane3::testPlaneSide() const
{
    if (m_isAligned)
    {
        Math::Vector3 vec_max = m_box.center() + Math::Vector3(m_box.extent());
        Math::Vector3 vec_min = m_box.center() - Math::Vector3(m_box.extent());
        if (m_plane.normal().x() < 0.0f)
        {
            const float t = vec_max.x();
            vec_max.x(vec_min.x());
            vec_min.x(t);
        }
        if (m_plane.normal().y() < 0.0f)
        {
            const float t = vec_max.y();
            vec_max.y(vec_min.y());
            vec_min.y(t);
        }
        if (m_plane.normal().z() < 0.0f)
        {
            const float t = vec_max.z();
            vec_max.z(vec_min.z());
            vec_min.z(t);
        }

        if (m_plane.normal().dot(vec_min) > m_plane.constant()) return Math::Plane3::SideOfPlane::positive;
        if (m_plane.normal().dot(vec_max) < m_plane.constant()) return Math::Plane3::SideOfPlane::negative;
        return Math::Plane3::SideOfPlane::overlap;
    }
    const std::array<float, 3> tmp =
    {
        m_box.extent(0) * (m_plane.normal().dot(m_box.axis(0))),
        m_box.extent(1) * (m_plane.normal().dot(m_box.axis(1))),
        m_box.extent(2) * (m_plane.normal().dot(m_box.axis(2))),
    };

    const float radius = std::abs(tmp[0]) + std::abs(tmp[1]) + std::abs(tmp[2]);

    const float signed_distance = m_plane.signedDistanceTo(m_box.center());

    if (signed_distance - radius >= 0.0f)
    {
        return Math::Plane3::SideOfPlane::positive;
    }

    if (signed_distance + radius <= 0.0f)
    {
        return Math::Plane3::SideOfPlane::negative;
    }

    return Math::Plane3::SideOfPlane::overlap;
}

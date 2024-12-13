#include "IntrLine3Box3.hpp"
#include "Math/MathGlobal.hpp"
#include <array>
#include <cassert>
#include <cmath>

using namespace Collision;

IntrLine3Box3::IntrLine3Box3(const Math::Line3& line, const Math::Box3& box) : m_line(line), m_box(box), m_quantity(0), m_lineT{}
{
    m_intersectionType = IntersectionType::point;
}

const Math::Line3& IntrLine3Box3::line() const
{
    return m_line;
}

const Math::Box3& IntrLine3Box3::box() const
{
    return m_box;
}

bool IntrLine3Box3::test()
{
    // NOLINTBEGIN(readability-identifier-naming)
    /** algorism from 3D game engine architecture p.520~p.521 & wildmagic code */
    /** 有點複雜的理論，還跟Minkowski difference有關 */
    std::array<float, 3> AWdU{};
    std::array<float, 3> AWxDdU{};

    const Math::Vector3 diff = m_line.origin() - m_box.center();
    const Math::Vector3 WxD = m_line.direction().cross(diff);

    AWdU[1] = std::abs(m_line.direction().dot(m_box.axis(1)));
    AWdU[2] = std::abs(m_line.direction().dot(m_box.axis(2)));
    AWxDdU[0] = std::abs(WxD.dot(m_box.axis(0)));
    float rhs = m_box.extent(1) * AWdU[2] + m_box.extent(2) * AWdU[1];
    if (AWxDdU[0] > rhs) return false;

    AWdU[0] = std::abs(m_line.direction().dot(m_box.axis(0)));
    AWxDdU[1] = std::abs(WxD.dot(m_box.axis(1)));
    rhs = m_box.extent(0) * AWdU[2] + m_box.extent(2) * AWdU[0];
    if (AWxDdU[1] > rhs) return false;

    AWxDdU[2] = std::abs(WxD.dot(m_box.axis(2)));
    rhs = m_box.extent(0) * AWdU[1] + m_box.extent(1) * AWdU[0];
    if (AWxDdU[2] > rhs) return false; // NOLINT(readability-simplify-boolean-expr)

    return true;
    // NOLINTEND(readability-identifier-naming)
}

bool IntrLine3Box3::find()
{
    float t0 = -Math::Constants::MAX_FLOAT;
    float t1 = Math::Constants::MAX_FLOAT;

    // convert linear component to box coordinates
    const Math::Vector3 diff = m_line.origin() - m_box.center();
    const Math::Vector3 b_origin(
        diff.dot(m_box.axis(0)),
        diff.dot(m_box.axis(1)),
        diff.dot(m_box.axis(2))
    );
    const Math::Vector3 b_direction(
        m_line.direction().dot(m_box.axis(0)),
        m_line.direction().dot(m_box.axis(1)),
        m_line.direction().dot(m_box.axis(2))
    );

    const bool is_not_all_clipped =
        clip(+b_direction.x(), -b_origin.x() - m_box.extent(0), t0, t1) &&
        clip(-b_direction.x(), +b_origin.x() - m_box.extent(0), t0, t1) &&
        clip(+b_direction.y(), -b_origin.y() - m_box.extent(1), t0, t1) &&
        clip(-b_direction.y(), +b_origin.y() - m_box.extent(1), t0, t1) &&
        clip(+b_direction.z(), -b_origin.z() - m_box.extent(2), t0, t1) &&
        clip(-b_direction.z(), +b_origin.z() - m_box.extent(2), t0, t1);

    if (is_not_all_clipped)
    {
        if (t1 > t0)
        {
            m_quantity = 2;
            m_point[0] = m_line.origin() + t0 * m_line.direction();
            m_point[1] = m_line.origin() + t1 * m_line.direction();
            m_lineT[0] = t0;
            m_lineT[1] = t1;
        }
        else
        {
            m_quantity = 1;
            m_point[0] = m_line.origin() + t0 * m_line.direction();
            m_lineT[0] = t0;
        }
    }
    else
    {
        m_quantity = 0;
    }

    return (m_quantity != 0);
}

bool IntrLine3Box3::clip(float denom, float numer, float& t0, float& t1)
{
    // Return value is 'true' if line segment intersects the current test
    // plane.  'false' is returned in which case the line segment
    // is entirely clipped.

    if (denom > 0.0f)
    {
        if (numer > denom * t1)
        {
            return false;
        }
        if (numer > denom * t0)
        {
            t0 = numer / denom;
        }
        return true;
    }
    if (denom < 0.0f)
    {
        if (numer > denom * t0)
        {
            return false;
        }
        if (numer > denom * t1)
        {
            t1 = numer / denom;
        }
        return true;
    }
    return numer <= 0.0f;
}

unsigned IntrLine3Box3::getQuantity() const
{
    return m_quantity;
}

const Math::Point3& IntrLine3Box3::getPoint(unsigned i) const
{
    assert(i < 2);
    return m_point[i];
}

float IntrLine3Box3::getLineT(unsigned i) const
{
    assert(i < 2);
    return m_lineT[i];
}


#include "IntrLine3Sphere3.hpp"
#include "Math/MathGlobal.hpp"
#include <array>
#include <cmath>
#include <cassert>

using namespace Collision;

IntrLine3Sphere3::IntrLine3Sphere3(const Math::Line3& line, const Math::Sphere3& sphere) : m_line(line), m_sphere(sphere), m_quantity(0), m_lineT{}
{
}

const Math::Line3& IntrLine3Sphere3::line() const
{
    return m_line;
}

const Math::Sphere3& IntrLine3Sphere3::sphere() const
{
    return m_sphere;
}

bool IntrLine3Sphere3::test()
{
    const Math::Vector3 diff = m_line.origin() - m_sphere.center();
    const float a0 = diff.dot(diff) - m_sphere.radius() * m_sphere.radius();
    const float a1 = m_line.direction().dot(diff);
    const float discr = a1 * a1 - a0;
    return discr >= 0.0f;
}

bool IntrLine3Sphere3::find()
{
    const Math::Vector3 diff = m_line.origin() - m_sphere.center();
    const float a0 = diff.dot(diff) - m_sphere.radius() * m_sphere.radius();
    const float a1 = m_line.direction().dot(diff);
    const float discr = a1 * a1 - a0;

    if (discr < 0.0f)
    {
        m_quantity = 0;
    }
    else if (discr >= Math::FloatCompare::zeroTolerance())
    {
        const float root = std::sqrt(discr);
        m_lineT[0] = -a1 - root;
        m_lineT[1] = -a1 + root;
        m_point[0] = m_line.origin() + m_lineT[0] * m_line.direction();
        m_point[1] = m_line.origin() + m_lineT[1] * m_line.direction();
        m_quantity = 2;
    }
    else
    {
        m_lineT[0] = -a1;
        m_point[0] = m_line.origin() + m_lineT[0] * m_line.direction();
        m_quantity = 1;
    }

    return m_quantity > 0;
}

unsigned IntrLine3Sphere3::getQuantity() const
{
    return m_quantity;
}

const Math::Point3& IntrLine3Sphere3::getPoint(unsigned i) const
{
    assert(i < m_quantity);
    return m_point[i];
}

float IntrLine3Sphere3::getLineT(unsigned i) const
{
    assert(i < m_quantity);
    return m_lineT[i];
}

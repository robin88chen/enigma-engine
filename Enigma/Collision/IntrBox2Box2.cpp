#include "IntrBox2Box2.hpp"
#include "Math/Box2.hpp"
#include <cmath>
#include <array>

using namespace Collision;

IntrBox2Box2::IntrBox2Box2(const Math::Box2& box0, const Math::Box2& box1) : m_box0(box0), m_box1(box1)
{
}

const Math::Box2& IntrBox2Box2::box0() const
{
    return m_box0;
}

const Math::Box2& IntrBox2Box2::box1() const
{
    return m_box1;
}

bool IntrBox2Box2::test()
{
    // convenience variables
    const std::array<Math::Vector2, 2>& axis_a = m_box0.axis();
    const std::array<Math::Vector2, 2>& axis_b = m_box1.axis();
    const std::array<float, 2>& extent_a = m_box0.extent();
    const std::array<float, 2>& extent_b = m_box1.extent();

    // compute difference of box centers, D = C1-C0
    const Math::Vector2 vec_diff = m_box1.center() - m_box0.center();

    std::array<std::array<float, 2>, 2> abs_a_dot_b{};

    // axis C0+t*A0
    abs_a_dot_b[0][0] = std::abs(axis_a[0].dot(axis_b[0]));
    abs_a_dot_b[0][1] = std::abs(axis_a[0].dot(axis_b[1]));
    float abs_a_dot_d = std::abs(axis_a[0].dot(vec_diff));
    float sum = extent_a[0] + extent_b[0] * abs_a_dot_b[0][0] + extent_b[1] * abs_a_dot_b[0][1];
    if (abs_a_dot_d > sum) return false;

    // axis C0+t*A1
    abs_a_dot_b[1][0] = std::abs(axis_a[1].dot(axis_b[0]));
    abs_a_dot_b[1][1] = std::abs(axis_a[1].dot(axis_b[1]));
    abs_a_dot_d = std::abs(axis_a[1].dot(vec_diff));
    sum = extent_a[1] + extent_b[0] * abs_a_dot_b[1][0] + extent_b[1] * abs_a_dot_b[1][1];
    if (abs_a_dot_d > sum) return false;

    // axis C0+t*B0
    abs_a_dot_d = std::abs(axis_b[0].dot(vec_diff));
    sum = extent_b[0] + extent_a[0] * abs_a_dot_b[0][0] + extent_a[1] * abs_a_dot_b[1][0];
    if (abs_a_dot_d > sum) return false;

    // axis C0+t*B1
    abs_a_dot_d = std::abs(axis_b[1].dot(vec_diff));
    sum = extent_b[1] + extent_a[0] * abs_a_dot_b[0][1] + extent_a[1] * abs_a_dot_b[1][1];
    if (abs_a_dot_d > sum) return false; // NOLINT(readability-simplify-boolean-expr)

    return true;
}


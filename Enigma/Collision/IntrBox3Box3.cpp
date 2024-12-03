#include "IntrBox3Box3.hpp"
#include "Math/Box3.hpp"
#include "Math/MathGlobal.hpp"
#include <cmath>

using namespace Collision;

IntrBox3Box3::IntrBox3Box3(const Math::Box3& box0, const Math::Box3& box1) : m_box0(box0), m_box1(box1)
{
}

const Math::Box3& IntrBox3Box3::box0() const
{
    return m_box0;
}

const Math::Box3& IntrBox3Box3::box1() const
{
    return m_box1;
}

bool IntrBox3Box3::test()
{
    // Cutoff for cosine of angles between box axes.  This is used to catch
    // the cases when at least one pair of axes are parallel.  If this happens,
    // there is no need to test for separation along the cross(A[i],B[j])
    // directions.
    constexpr float CUTOFF = 1.0f - Math::FloatCompare::ZERO_TOLERANCE;
    bool is_exists_parallel_pair = false;

    // convenience variables
    const std::array<Math::Vector3, 3>& axis_a = m_box0.axis();
    const std::array<Math::Vector3, 3>& axis_b = m_box1.axis();
    const std::array<float, 3>& extent_a = m_box0.extent();
    const std::array<float, 3>& extent_b = m_box1.extent();

    // compute difference of box centers, D = C1-C0
    const Math::Vector3 vec_diff = m_box1.center() - m_box0.center();

    std::array<std::array<float, 3>, 3> mx_c{};     // matrix C = A^T B, c_{ij} = dot(A_i,B_j)
    std::array<std::array<float, 3>, 3> abs_c{};  // |c_{ij}|
    std::array<float, 3> axis_dot_diff{};        // dot(A_i,D)
    //float radius0, radius1, radius;   // interval radii and distance between centers
    //float radius01;           // = R0 + R1

    // axis C0+t*A0
    for (int i = 0; i < 3; i++)
    {
        mx_c[0][i] = axis_a[0].dot(axis_b[i]);
        abs_c[0][i] = std::abs(mx_c[0][i]);
        if (abs_c[0][i] > CUTOFF) is_exists_parallel_pair = true;
    }
    axis_dot_diff[0] = axis_a[0].dot(vec_diff);
    float radius = std::abs(axis_dot_diff[0]);
    float radius1 = extent_b[0] * abs_c[0][0] + extent_b[1] * abs_c[0][1] + extent_b[2] * abs_c[0][2];
    float radius01 = extent_a[0] + radius1;
    if (radius > radius01) return false;

    // axis C0+t*A1
    for (int i = 0; i < 3; i++)
    {
        mx_c[1][i] = axis_a[1].dot(axis_b[i]);
        abs_c[1][i] = std::abs(mx_c[1][i]);
        if (abs_c[1][i] > CUTOFF) is_exists_parallel_pair = true;
    }
    axis_dot_diff[1] = axis_a[1].dot(vec_diff);
    radius = std::abs(axis_dot_diff[1]);
    radius1 = extent_b[0] * abs_c[1][0] + extent_b[1] * abs_c[1][1] + extent_b[2] * abs_c[1][2];
    radius01 = extent_a[1] + radius1;
    if (radius > radius01) return false;

    // axis C0+t*A2
    for (int i = 0; i < 3; i++)
    {
        mx_c[2][i] = axis_a[2].dot(axis_b[i]);
        abs_c[2][i] = std::abs(mx_c[2][i]);
        if (abs_c[2][i] > CUTOFF) is_exists_parallel_pair = true;
    }
    axis_dot_diff[2] = axis_a[2].dot(vec_diff);
    radius = std::abs(axis_dot_diff[2]);
    radius1 = extent_b[0] * abs_c[2][0] + extent_b[1] * abs_c[2][1] + extent_b[2] * abs_c[2][2];
    radius01 = extent_a[2] + radius1;
    if (radius > radius01) return false;

    // axis C0+t*B0
    radius = std::abs(axis_b[0].dot(vec_diff));
    float radius0 = extent_a[0] * abs_c[0][0] + extent_a[1] * abs_c[1][0] + extent_a[2] * abs_c[2][0];
    radius01 = radius0 + extent_b[0];
    if (radius > radius01) return false;

    // axis C0+t*B1
    radius = std::abs(axis_b[1].dot(vec_diff));
    radius0 = extent_a[0] * abs_c[0][1] + extent_a[1] * abs_c[1][1] + extent_a[2] * abs_c[2][1];
    radius01 = radius0 + extent_b[1];
    if (radius > radius01) return false;

    // axis C0+t*B2
    radius = std::abs(axis_b[2].dot(vec_diff));
    radius0 = extent_a[0] * abs_c[0][2] + extent_a[1] * abs_c[1][2] + extent_a[2] * abs_c[2][2];
    radius01 = radius0 + extent_b[2];
    if (radius > radius01) return false;

    // At least one pair of box axes was parallel, so the separation is
    // effectively in 2D where checking the "edge" normals is sufficient for
    // the separation of the boxes.
    if (is_exists_parallel_pair) return true;

    // axis C0+t*A0xB0
    radius = std::abs(axis_dot_diff[2] * mx_c[1][0] - axis_dot_diff[1] * mx_c[2][0]);
    radius0 = extent_a[1] * abs_c[2][0] + extent_a[2] * abs_c[1][0];
    radius1 = extent_b[1] * abs_c[0][2] + extent_b[2] * abs_c[0][1];
    radius01 = radius0 + radius1;
    if (radius > radius01) return false;

    // axis C0+t*A0xB1
    radius = std::abs(axis_dot_diff[2] * mx_c[1][1] - axis_dot_diff[1] * mx_c[2][1]);
    radius0 = extent_a[1] * abs_c[2][1] + extent_a[2] * abs_c[1][1];
    radius1 = extent_b[0] * abs_c[0][2] + extent_b[2] * abs_c[0][0];
    radius01 = radius0 + radius1;
    if (radius > radius01) return false;

    // axis C0+t*A0xB2
    radius = std::abs(axis_dot_diff[2] * mx_c[1][2] - axis_dot_diff[1] * mx_c[2][2]);
    radius0 = extent_a[1] * abs_c[2][2] + extent_a[2] * abs_c[1][2];
    radius1 = extent_b[0] * abs_c[0][1] + extent_b[1] * abs_c[0][0];
    radius01 = radius0 + radius1;
    if (radius > radius01) return false;

    // axis C0+t*A1xB0
    radius = std::abs(axis_dot_diff[0] * mx_c[2][0] - axis_dot_diff[2] * mx_c[0][0]);
    radius0 = extent_a[0] * abs_c[2][0] + extent_a[2] * abs_c[0][0];
    radius1 = extent_b[1] * abs_c[1][2] + extent_b[2] * abs_c[1][1];
    radius01 = radius0 + radius1;
    if (radius > radius01) return false;

    // axis C0+t*A1xB1
    radius = std::abs(axis_dot_diff[0] * mx_c[2][1] - axis_dot_diff[2] * mx_c[0][1]);
    radius0 = extent_a[0] * abs_c[2][1] + extent_a[2] * abs_c[0][1];
    radius1 = extent_b[0] * abs_c[1][2] + extent_b[2] * abs_c[1][0];
    radius01 = radius0 + radius1;
    if (radius > radius01) return false;

    // axis C0+t*A1xB2
    radius = std::abs(axis_dot_diff[0] * mx_c[2][2] - axis_dot_diff[2] * mx_c[0][2]);
    radius0 = extent_a[0] * abs_c[2][2] + extent_a[2] * abs_c[0][2];
    radius1 = extent_b[0] * abs_c[1][1] + extent_b[1] * abs_c[1][0];
    radius01 = radius0 + radius1;
    if (radius > radius01) return false;

    // axis C0+t*A2xB0
    radius = std::abs(axis_dot_diff[1] * mx_c[0][0] - axis_dot_diff[0] * mx_c[1][0]);
    radius0 = extent_a[0] * abs_c[1][0] + extent_a[1] * abs_c[0][0];
    radius1 = extent_b[1] * abs_c[2][2] + extent_b[2] * abs_c[2][1];
    radius01 = radius0 + radius1;
    if (radius > radius01) return false;

    // axis C0+t*A2xB1
    radius = std::fabs(axis_dot_diff[1] * mx_c[0][1] - axis_dot_diff[0] * mx_c[1][1]);
    radius0 = extent_a[0] * abs_c[1][1] + extent_a[1] * abs_c[0][1];
    radius1 = extent_b[0] * abs_c[2][2] + extent_b[2] * abs_c[2][0];
    radius01 = radius0 + radius1;
    if (radius > radius01) return false;

    // axis C0+t*A2xB2
    radius = std::abs(axis_dot_diff[1] * mx_c[0][2] - axis_dot_diff[0] * mx_c[1][2]);
    radius0 = extent_a[0] * abs_c[1][2] + extent_a[1] * abs_c[0][2];
    radius1 = extent_b[0] * abs_c[2][1] + extent_b[1] * abs_c[2][0];
    radius01 = radius0 + radius1;
    if (radius > radius01) return false; // NOLINT(readability-simplify-boolean-expr)

    return true;
}

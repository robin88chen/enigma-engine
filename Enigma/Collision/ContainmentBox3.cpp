#include "ContainmentBox3.hpp"
#include "Math/Box3.hpp"
#include "Math/MathGlobal.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Vector3.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Vector4.hpp"
#include "Math/Sphere3.hpp"
#include "Math/EigenDecompose.hpp"
#include <cassert>
#include <cmath>

using namespace Collision;

//----------------------------------------------------------------------------
// Merge Boxes
// 中心點為兩個Box中心點的中心，再用Quaternion取得兩組軸向的旋轉值，取出slerp平均值
// 最後再以兩個Box的頂點取出最大最小值，得到邊長
// Box要將三個軸取出Major x,y,z，這樣子在做Quaternion時，才會取得比較小的平均旋轉值，
// 否則會因為角度差異太大，造成算出來的Box比實際需要大很多
//----------------------------------------------------------------------------
Math::Box3 ContainmentBox3::mergeBoxes(const Math::Box3& box0, const Math::Box3& box1)
{
    // construct a box that contains the input boxes
    std::array<Math::Vector3, 3> merged_axis{};
    const Math::Box3 box_major0 = box0.swapToMajorAxis();
    const Math::Box3 box_major1 = box1.swapToMajorAxis();

    // The first guess at the box center.  This value will be updated later
    // after the input box vertices are projected onto axes determined by an
    // average of box axes.
    Math::Point3 center = 0.5f * (box_major0.center() + box_major1.center());

    // A box's axes, when viewed as the columns of a matrix, form a rotation
    // matrix.  The input box axes are converted to quaternions.  The average
    // quaternion is computed, then normalized to unit length.  The result is
    // the slerp of the two input quaternions with t-value of 1/2.  The result
    // is converted back to a rotation matrix and its columns are selected as
    // the merged box axes.
    const Math::Quaternion q0 = Math::Quaternion::fromRotationMatrix(Math::Matrix3::fromColumnVectors(box_major0.axis()));
    Math::Quaternion q1 = Math::Quaternion::fromRotationMatrix(Math::Matrix3::fromColumnVectors(box_major1.axis()));
    if (q0.dot(q1) < 0.0f)
    {
        q1 = -q1;
    }

    Math::Quaternion q = q0 + q1;
    const float inv_length = 1.0f / std::sqrt(q.dot(q));
    q = inv_length * q;
    const Math::Matrix3 rot_merge = q.toRotationMatrix();
    merged_axis[0] = rot_merge.getColumn(0);
    merged_axis[1] = rot_merge.getColumn(1);
    merged_axis[2] = rot_merge.getColumn(2);

    // Project the input box vertices onto the merged-box axes.  Each axis
    // D[i] containing the current center C has a minimum projected value
    // pmin[i] and a maximum projected value pmax[i].  The corresponding end
    // points on the axes are C+pmin[i]*D[i] and C+pmax[i]*D[i].  The point C
    // is not necessarily the midpoint for any of the intervals.  The actual
    // box center will be adjusted from C to a point C' that is the midpoint
    // of each interval,
    //   C' = C + sum_{i=0}^2 0.5*(pmin[i]+pmax[i])*D[i]
    // The box extents are
    //   e[i] = 0.5*(pmax[i]-pmin[i])

    Math::Vector3 vec_min = Math::Vector3::ZERO;
    Math::Vector3 vec_max = Math::Vector3::ZERO;

    std::array<Math::Point3, Math::Box3::VERTICES_COUNT> vertex = box_major0.computeVertices();
    for (unsigned i = 0; i < Math::Box3::VERTICES_COUNT; i++)
    {
        const Math::Vector3 diff = vertex[i] - center;
        for (unsigned j = 0; j < 3; j++)
        {
            const float dot = diff.dot(merged_axis[j]);
            if (dot > vec_max[j])
            {
                vec_max[j] = dot;
            }
            else if (dot < vec_min[j])
            {
                vec_min[j] = dot;
            }
        }
    }

    vertex = box_major1.computeVertices();
    for (unsigned i = 0; i < Math::Box3::VERTICES_COUNT; i++)
    {
        const Math::Vector3 diff = vertex[i] - center;
        for (unsigned j = 0; j < 3; j++)
        {
            const float dot = diff.dot(merged_axis[j]);
            if (dot > vec_max[j])
            {
                vec_max[j] = dot;
            }
            else if (dot < vec_min[j])
            {
                vec_min[j] = dot;
            }
        }
    }

    // [kMin,kMax] is the axis-aligned box in the coordinate system of the
    // merged box axes.  Update the current box center to be the center of
    // the new box.  Compute the extents based on the new center.
    std::array<float, 3> extent{};
    for (unsigned j = 0; j < 3; j++)
    {
        center += (0.5f * (vec_max[j] + vec_min[j])) * merged_axis[j];
        extent[j] = 0.5f * (vec_max[j] - vec_min[j]);
    }

    return { center, merged_axis, extent };
}

Math::Box3 ContainmentBox3::mergeAlignedBoxes(const Math::Box3& box0, const Math::Box3& box1)
{
    // 取兩個box的最大最小位置
    Math::Point3 vec_max = box0.center() + Math::Vector3(box0.extent());
    Math::Point3 vec_min = box0.center() + (-Math::Vector3(box0.extent()));

    const Math::Point3 vec_max1 = box1.center() + Math::Vector3(box1.extent());
    const Math::Point3 vec_min1 = box1.center() + (-Math::Vector3(box1.extent()));

    if (vec_max.x() < vec_max1.x())
    {
        vec_max.x(vec_max1.x());
    }
    if (vec_max.y() < vec_max1.y())
    {
        vec_max.y(vec_max1.y());
    }
    if (vec_max.z() < vec_max1.z())
    {
        vec_max.z(vec_max1.z());
    }
    if (vec_min.x() > vec_min1.x())
    {
        vec_min.x(vec_min1.x());
    }
    if (vec_min.y() > vec_min1.y())
    {
        vec_min.y(vec_min1.y());
    }
    if (vec_min.z() > vec_min1.z())
    {
        vec_min.z(vec_min1.z());
    }

    Math::Box3 box;
    box.center(0.5f * (vec_max + vec_min));
    const Math::Vector3 vec_diff = vec_max - box.center();
    box.extent(0, vec_diff.x());
    box.extent(1, vec_diff.y());
    box.extent(2, vec_diff.z());

    return box;
}

Math::Box3 ContainmentBox3::computeAlignedBox(const std::vector<Math::Point3>& pos)
{
    const float minimum_scale = Math::FloatCompare::zeroTolerance() * 10.f;
    assert(!pos.empty());

    const auto quantity = static_cast<unsigned>(pos.size());
    Math::Point3 vec_min = pos[0];
    Math::Point3 vec_max = pos[0];
    for (unsigned i = 1; i < quantity; i++)
    {
        if (pos[i].x() > vec_max.x()) vec_max.x(pos[i].x());
        if (pos[i].y() > vec_max.y()) vec_max.y(pos[i].y());
        if (pos[i].z() > vec_max.z()) vec_max.z(pos[i].z());
        if (pos[i].x() < vec_min.x()) vec_min.x(pos[i].x());
        if (pos[i].y() < vec_min.y()) vec_min.y(pos[i].y());
        if (pos[i].z() < vec_min.z()) vec_min.z(pos[i].z());
    }
    const Math::Point3 center = 0.5f * (vec_max + vec_min);
    Math::Vector3 extend = vec_max - center;
    // 加一個基本大小
    if (extend.x() <= Math::FloatCompare::zeroTolerance()) extend.x(minimum_scale);
    if (extend.y() <= Math::FloatCompare::zeroTolerance()) extend.y(minimum_scale);
    if (extend.z() <= Math::FloatCompare::zeroTolerance()) extend.z(minimum_scale);
    return { center, Math::Vector3::UNIT_X, Math::Vector3::UNIT_Y, Math::Vector3::UNIT_Z, extend.x(), extend.y(), extend.z() };
}

Math::Box3 ContainmentBox3::computeAlignedBox(const std::vector<Math::Vector4>& pos)
{
    const float minimum_scale = Math::FloatCompare::zeroTolerance() * 10.f;
    assert(!pos.empty());

    const auto quantity = static_cast<unsigned>(pos.size());
    Math::Point3 vec_min(pos[0].x(), pos[0].y(), pos[0].z());
    Math::Point3 vec_max = vec_min;
    for (unsigned int i = 1; i < quantity; i++)
    {
        if (pos[i].x() > vec_max.x()) vec_max.x(pos[i].x());
        if (pos[i].y() > vec_max.y()) vec_max.y(pos[i].y());
        if (pos[i].z() > vec_max.z()) vec_max.z(pos[i].z());
        if (pos[i].x() < vec_min.x()) vec_min.x(pos[i].x());
        if (pos[i].y() < vec_min.y()) vec_min.y(pos[i].y());
        if (pos[i].z() < vec_min.z()) vec_min.z(pos[i].z());
    }
    const Math::Point3 center = 0.5f * (vec_max + vec_min);
    Math::Vector3 extend = vec_max - center;
    // 加一個基本大小
    if (extend.x() <= Math::FloatCompare::zeroTolerance()) extend.x(minimum_scale);
    if (extend.y() <= Math::FloatCompare::zeroTolerance()) extend.y(minimum_scale);
    if (extend.z() <= Math::FloatCompare::zeroTolerance()) extend.z(minimum_scale);
    return { center, Math::Vector3::UNIT_X, Math::Vector3::UNIT_Y, Math::Vector3::UNIT_Z, extend.x(), extend.y(), extend.z() };
}

Math::Box3 ContainmentBox3::computeAlignedBox(const float* vert, unsigned int pitch, unsigned int quantity)
{
    const float minimum_scale = Math::FloatCompare::zeroTolerance() * 10.f;
    assert(vert != nullptr);
    assert(quantity != 0);

    Math::Point3 vec_min(vert[0], vert[1], vert[2]);
    Math::Point3 vec_max = vec_min;
    unsigned int index = pitch;
    for (unsigned int i = 1; i < quantity; i++)
    {
        if (vert[index] > vec_max.x()) vec_max.x(vert[index]);
        if (vert[index + 1] > vec_max.y()) vec_max.y(vert[index + 1]);
        if (vert[index + 2] > vec_max.z()) vec_max.z(vert[index + 2]);
        if (vert[index] < vec_min.x()) vec_min.x(vert[index]);
        if (vert[index + 1] < vec_min.y()) vec_min.y(vert[index + 1]);
        if (vert[index + 2] < vec_min.z()) vec_min.z(vert[index + 2]);
        index += pitch;
    }
    const Math::Point3 center = 0.5f * (vec_max + vec_min);
    Math::Vector3 extend = vec_max - center;
    // 加一個基本大小
    if (extend.x() <= Math::FloatCompare::zeroTolerance()) extend.x(minimum_scale);
    if (extend.y() <= Math::FloatCompare::zeroTolerance()) extend.y(minimum_scale);
    if (extend.z() <= Math::FloatCompare::zeroTolerance()) extend.z(minimum_scale);
    return { center, Math::Vector3::UNIT_X, Math::Vector3::UNIT_Y, Math::Vector3::UNIT_Z, extend.x(), extend.y(), extend.z() };
}

Math::Box3 ContainmentBox3::computeOrientedBox(const std::vector<Math::Point3>& pos)
{
    assert(!pos.empty());

    const auto quantity = static_cast<unsigned>(pos.size());
    Math::Point3 center = pos[0];
    for (unsigned int i = 1; i < quantity; i++)
    {
        center += pos[i];
    }
    const float inv_quantity = 1.0f / static_cast<float>(quantity);
    center = center * inv_quantity;

    float sum_xx = 0.0f;
    float sum_xy = 0.0f;
    float sum_xz = 0.0f;
    float sum_yy = 0.0f;
    float sum_yz = 0.0f;
    float sum_zz = 0.0f;
    for (unsigned int i = 0; i < quantity; i++)
    {
        const Math::Vector3 diff = pos[i] - center;
        sum_xx += diff.x() * diff.x();
        sum_xy += diff.x() * diff.y();
        sum_xz += diff.x() * diff.z();
        sum_yy += diff.y() * diff.y();
        sum_yz += diff.y() * diff.z();
        sum_zz += diff.z() * diff.z();
    }
    sum_xx *= inv_quantity;
    sum_xy *= inv_quantity;
    sum_xz *= inv_quantity;
    sum_yy *= inv_quantity;
    sum_yz *= inv_quantity;
    sum_zz *= inv_quantity;

    Math::Matrix3 mx_eigen;
    mx_eigen[0][0] = sum_xx;
    mx_eigen[0][1] = sum_xy;
    mx_eigen[0][2] = sum_xz;
    mx_eigen[1][0] = sum_xy;
    mx_eigen[1][1] = sum_yy;
    mx_eigen[1][2] = sum_yz;
    mx_eigen[2][0] = sum_xz;
    mx_eigen[2][1] = sum_yz;
    mx_eigen[2][2] = sum_zz;

    const Math::EigenDecompose<Math::Matrix3> eigen_decompose = Math::eigenDecomposition(mx_eigen);

    Math::Box3 box;
    box.center(center);
    box.axis({ eigen_decompose.m_rot.getColumn(0), eigen_decompose.m_rot.getColumn(1), eigen_decompose.m_rot.getColumn(2) });

    Math::Vector3 vec_trans = pos[0] - box.center();
    Math::Vector3 vec_min(vec_trans.dot(box.axis(0)), vec_trans.dot(box.axis(1)), vec_trans.dot(box.axis(2)));
    Math::Vector3 vec_max = vec_min;
    for (unsigned int i = 1; i < quantity; i++)
    {
        vec_trans = pos[i] - box.center();
        float dot = vec_trans.dot(box.axis(0));
        if (dot < vec_min.x()) vec_min.x(dot);
        if (dot > vec_max.x()) vec_max.x(dot);
        dot = vec_trans.dot(box.axis(1));
        if (dot < vec_min.y()) vec_min.y(dot);
        if (dot > vec_max.y()) vec_max.y(dot);
        dot = vec_trans.dot(box.axis(2));
        if (dot < vec_min.z()) vec_min.z(dot);
        if (dot > vec_max.z()) vec_max.z(dot);
    }

    Math::Point3 center_new = box.center();
    center_new += (0.5f * (vec_min.x() + vec_max.x()) * box.axis(0)
        + 0.5f * (vec_min.y() + vec_max.y()) * box.axis(1)
        + 0.5f * (vec_min.z() + vec_max.z()) * box.axis(2));
    box.center(center_new);
    box.extent(0, 0.5f * (vec_max.x() - vec_min.x()));
    box.extent(1, 0.5f * (vec_max.y() - vec_min.y()));
    box.extent(2, 0.5f * (vec_max.z() - vec_min.z()));

    // 將axis 0,1,2調整到主要為x,y,z (測試一下看merge box會不會比較正確)
    return box.swapToMajorAxis();
}

Math::Box3 ContainmentBox3::computeOrientedBox(const std::vector<Math::Vector4>& pos4)
{
    assert(!pos4.empty());

    const auto quantity = static_cast<unsigned>(pos4.size());
    std::vector<Math::Point3> pos(quantity);
    for (unsigned int i = 0; i < quantity; i++)
    {
        pos[i] = Math::Point3(pos4[i].x(), pos4[i].y(), pos4[i].z());
    }

    return computeOrientedBox(pos);
}

Math::Box3 ContainmentBox3::computeOrientedBox(const float* vert, unsigned int pitch, unsigned int quantity)
{
    assert(vert != nullptr);
    assert(quantity != 0);

    std::vector<Math::Point3> pos(quantity);
    unsigned int index = 0;
    for (unsigned int i = 0; i < quantity; i++)
    {
        pos[i] = Math::Point3(vert[index], vert[index + 1], vert[index + 2]);
        index += pitch;
    }

    return computeOrientedBox(pos);
}

bool ContainmentBox3::testBox3EnvelopBox3(const Math::Box3& box0, const Math::Box3& box1)
{
    std::array<Math::Point3, Math::Box3::VERTICES_COUNT> vertex = box1.computeVertices();
    for (unsigned int i = 0; i < Math::Box3::VERTICES_COUNT; i++)
    {
        if (!box0.contains(vertex[i])) return false;
    }
    return true;
}

bool ContainmentBox3::testBox3EnvelopSphere3(const Math::Box3& box0, const Math::Sphere3& sphere1)
{
    const Math::Vector3 diff = sphere1.center() - box0.center();
    if (std::abs(diff.dot(box0.axis(0))) + sphere1.radius() > box0.extent(0)) return false;
    if (std::abs(diff.dot(box0.axis(1))) + sphere1.radius() > box0.extent(1)) return false;
    if (std::abs(diff.dot(box0.axis(2))) + sphere1.radius() > box0.extent(2)) return false;
    return true;
}

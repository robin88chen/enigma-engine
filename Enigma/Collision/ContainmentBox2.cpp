#include "ContainmentBox2.hpp"
#include "Math/Box2.hpp"
#include "Math/Sphere2.hpp"
#include <array>
#include <cmath>

using namespace Collision;

Math::Box2 ContainmentBox2::mergeBoxes(const Math::Box2& box0, const Math::Box2& box1)
{
    // Construct a box that contains the input boxes.

    // The first guess at the box center.  This value will be updated later
    // after the input box vertices are projected onto axes determined by an
    // average of box axes.
    Math::Vector2 center = 0.5f * (box0.center() + box1.center());

    // The merged box axes are the averages of the input box axes.  The
    // axes of the second box are negated, if necessary, so they form acute
    // angles with the axes of the first box.
    std::array<Math::Vector2, 2> box_axis{};
    if (box0.axis(0).dot(box1.axis(0)) >= 0.0f)
    {
        box_axis[0] = 0.5f * (box0.axis(0) + box1.axis(0));
        box_axis[0].normalizeSelf();
    }
    else
    {
        box_axis[0] = 0.5f * (box0.axis(0) - box1.axis(0));
        box_axis[0].normalizeSelf();
    }
    box_axis[1] = -box_axis[0].perpendicular();

    // Project the input box vertices onto the merged-box axes.  Each axis
    // D[i] containing the current center C has a minimum projected value
    // min[i] and a maximum projected value max[i].  The corresponding end
    // points on the axes are C+min[i]*D[i] and C+max[i]*D[i].  The point C
    // is not necessarily the midpoint for any of the intervals.  The actual
    // box center will be adjusted from C to a point C' that is the midpoint
    // of each interval,
    //   C' = C + sum_{i=0}^1 0.5*(min[i]+max[i])*D[i]
    // The box extents are
    //   e[i] = 0.5*(max[i]-min[i])

    Math::Vector2 pmin = Math::Vector2::ZERO;
    Math::Vector2 pmax = Math::Vector2::ZERO;

    std::array<Math::Vector2, Math::Box2::VERTICES_COUNT> vertex = box0.computeVertices();
    for (unsigned i = 0; i < Math::Box2::VERTICES_COUNT; ++i)
    {
        const Math::Vector2 diff = vertex[i] - center;
        for (unsigned j = 0; j < 2; ++j)
        {
            const float dot = diff.dot(box_axis[j]);
            if (dot > pmax[j])
            {
                pmax[j] = dot;
            }
            else if (dot < pmin[j])
            {
                pmin[j] = dot;
            }
        }
    }

    vertex = box1.computeVertices();
    for (unsigned i = 0; i < Math::Box2::VERTICES_COUNT; ++i)
    {
        const Math::Vector2 diff = vertex[i] - center;
        for (unsigned j = 0; j < 2; ++j)
        {
            const float dot = diff.dot(box_axis[j]);
            if (dot > pmax[j])
            {
                pmax[j] = dot;
            }
            else if (dot < pmin[j])
            {
                pmin[j] = dot;
            }
        }
    }

    // [min,max] is the axis-aligned box in the coordinate system of the
    // merged box axes.  Update the current box center to be the center of
    // the new box.  Compute the extents based on the new center.
    std::array<float, 2> extent{};
    for (unsigned j = 0; j < 2; ++j)
    {
        center += box_axis[j] * (0.5f * (pmax[j] + pmin[j]));
        extent[j] = 0.5f * (pmax[j] - pmin[j]);
    }

    return { center, box_axis, extent };
}

bool ContainmentBox2::testBox2EnvelopBox2(const Math::Box2& box0, const Math::Box2& box1)
{
    std::array<Math::Vector2, Math::Box2::VERTICES_COUNT> vertex = box1.computeVertices();
    for (unsigned int i = 0; i < Math::Box2::VERTICES_COUNT; i++)
    {
        const Math::Vector2 diff = vertex[i] - box0.center();
        if (std::abs(diff.dot(box0.axis(0))) > box0.extent(0)) return false;
        if (std::abs(diff.dot(box0.axis(1))) > box0.extent(1)) return false;
    }
    return true;
}

bool ContainmentBox2::testBox2EnvelopSphere2(const Math::Box2& box0, const Math::Sphere2& sphere1)
{
    const Math::Vector2 diff = sphere1.center() - box0.center();
    if (std::abs(diff.dot(box0.axis(0))) + sphere1.radius() > box0.extent(0)) return false;
    if (std::abs(diff.dot(box0.axis(1))) + sphere1.radius() > box0.extent(1)) return false;
    return true;
}

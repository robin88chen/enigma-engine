#include "ContainmentSphere2.hpp"
#include "Math/Sphere2.hpp"
#include "Math/MathGlobal.hpp"
#include <cmath>

using namespace Collision;

Math::Sphere2 ContainmentSphere2::mergeSpheres(const Math::Sphere2& sphere0, const Math::Sphere2& sphere1)
{
    const Math::Vector2 center_diff = sphere1.center() - sphere0.center();
    const float sqr_length = center_diff.squaredLength(); // 圓心的距離
    const float radius_diff = sphere1.radius() - sphere0.radius();
    const float radius_diff_sqr = radius_diff * radius_diff; // 半徑的差距

    if (radius_diff_sqr >= sqr_length) // 圓心的距離比半徑差距小，表示完全被包含
    {
        return (radius_diff >= 0.0f ? sphere1 : sphere0);
    }

    const float length = std::sqrt(sqr_length);
    Math::Sphere2 sphere;

    if (length > Math::FloatCompare::zeroTolerance())
    {
        const float coeff = (length + radius_diff) / (2.0f * length);
        sphere.center(sphere0.center() + coeff * center_diff);
    }
    else
    {
        sphere.center(sphere0.center());
    }

    sphere.radius(0.5f * (length + sphere0.radius() + sphere1.radius()));

    return sphere;
}

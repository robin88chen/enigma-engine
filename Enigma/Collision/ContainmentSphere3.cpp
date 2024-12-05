#include "ContainmentSphere3.hpp"
#include "Math/Sphere3.hpp"
#include "Math/MathGlobal.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include <cassert>
#include <cmath>

using namespace Collision;

Math::Sphere3 ContainmentSphere3::mergeSpheres(const Math::Sphere3& sphere0, const Math::Sphere3& sphere1)
{
    const Math::Vector3 center_diff = sphere1.center() - sphere0.center();
    const float sqr_length = center_diff.squaredLength();
    const float radius_diff = sphere1.radius() - sphere0.radius();

    if (const float radius_diff_sqr = radius_diff * radius_diff; radius_diff_sqr >= sqr_length)
    {
        return (radius_diff >= 0.0f ? sphere1 : sphere0);
    }

    const float length = std::sqrt(sqr_length);
    Math::Sphere3 sphere;

    if (length > Math::FloatCompare::ZERO_TOLERANCE)
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

Math::Sphere3 ContainmentSphere3::computeAverageSphere(const std::vector<Math::Vector3>& pos)
{
    assert(!pos.empty());
    const auto quantity = static_cast<unsigned>(pos.size());
    Math::Vector3 center = pos[0];
    for (unsigned int i = 1; i < quantity; i++)
    {
        center += pos[i];
    }
    center /= static_cast<float>(quantity);
    float sq_radius = 0.0f;
    for (unsigned int i = 0; i < quantity; i++)
    {
        const Math::Vector3 diff = pos[i] - center;
        const float diff_length = diff.squaredLength();
        if (diff_length > sq_radius) sq_radius = diff_length;
    }
    return { center, std::sqrt(sq_radius) };
}

Math::Sphere3 ContainmentSphere3::computeAverageSphere(const std::vector<Math::Vector4>& pos)
{
    assert(!pos.empty());
    const auto quantity = static_cast<unsigned>(pos.size());
    Math::Vector3 center(pos[0].x(), pos[0].y(), pos[0].z());
    for (unsigned int i = 1; i < quantity; i++)
    {
        center += Math::Vector3(pos[i].x(), pos[i].y(), pos[i].z());
    }
    center /= static_cast<float>(quantity);
    float sq_radius = 0.0f;
    for (unsigned int i = 0; i < quantity; i++)
    {
        const Math::Vector3 diff = Math::Vector3(pos[i].x(), pos[i].y(), pos[i].z()) - center;
        const float diff_length = diff.squaredLength();
        if (diff_length > sq_radius) sq_radius = diff_length;
    }
    return { center, std::sqrt(sq_radius) };
}

Math::Sphere3 ContainmentSphere3::computeAverageSphere(const float* vert, unsigned int pitch, unsigned int quantity)
{
    assert(vert != nullptr);
    assert(quantity != 0);
    Math::Vector3 center(vert[0], vert[1], vert[2]);
    unsigned int index = pitch;
    for (unsigned int i = 1; i < quantity; i++)
    {
        center += Math::Vector3(vert[index], vert[index + 1], vert[index + 2]);
        index += pitch;
    }
    center /= static_cast<float>(quantity);
    float sq_radius = 0.0f;
    index = 0;
    for (unsigned int i = 0; i < quantity; i++)
    {
        const Math::Vector3 diff = Math::Vector3(vert[index], vert[index + 1], vert[index + 2]) - center;
        const float diff_length = diff.squaredLength();
        if (diff_length > sq_radius) sq_radius = diff_length;
    }
    return { center, std::sqrt(sq_radius) };
}


/*********************************************************************
 * \file   ContainmentSphere3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef CONTAINMENT_SPHERE3_HPP
#define CONTAINMENT_SPHERE3_HPP

#include <vector>
namespace Math
{
    class Sphere3;
    class Vector3;
    class Vector4;
}

namespace Collision
{
    class ContainmentSphere3
    {
    public:
        static Math::Sphere3 mergeSpheres(const Math::Sphere3& sphere0, const Math::Sphere3& sphere1);
        static Math::Sphere3 computeAverageSphere(const std::vector<Math::Vector3>& pos);
        static Math::Sphere3 computeAverageSphere(const std::vector<Math::Vector4>& pos);
        static Math::Sphere3 computeAverageSphere(const float* vert, unsigned int pitch, unsigned int quantity);
    };
}

#endif // CONTAINMENT_SPHERE3_HPP

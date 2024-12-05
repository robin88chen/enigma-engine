/*********************************************************************
 * \file   ContainmentSphere2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef CONTAINMENT_SPHERE2_HPP
#define CONTAINMENT_SPHERE2_HPP

namespace Math
{
    class Sphere2;
}

namespace Collision
{
    class ContainmentSphere2
    {
    public:
        static Math::Sphere2 mergeSpheres(const Math::Sphere2& sphere0, const Math::Sphere2& sphere1);
    };
}

#endif // CONTAINMENT_SPHERE2_HPP

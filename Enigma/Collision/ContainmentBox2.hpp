/*********************************************************************
 * \file   ContainmentBox2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef CONTAINMENT_BOX2_HPP
#define CONTAINMENT_BOX2_HPP

namespace Math
{
    class Box2;
    class Sphere2;
}

namespace Collision
{
    class ContainmentBox2
    {
    public:
        static Math::Box2 mergeBoxes(const Math::Box2& box0, const Math::Box2& box1);
        static bool testBox2EnvelopBox2(const Math::Box2& box0, const Math::Box2& box1);
        static bool testBox2EnvelopSphere2(const Math::Box2& box0, const Math::Sphere2& sphere1);
    };
}

#endif // CONTAINMENT_BOX2_HPP

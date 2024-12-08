﻿/*********************************************************************
 * \file   ContainmentBox3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef CONTAINMENT_BOX3_HPP
#define CONTAINMENT_BOX3_HPP

#include <vector>
namespace Math
{
    class Box3;
    class Vector3;
    class Vector4;
}

namespace Collision
{
    class ContainmentBox3
    {
    public:
        static Math::Box3 mergeBoxes(const Math::Box3& box0, const Math::Box3& box1);
        static Math::Box3 mergeAlignedBoxes(const Math::Box3& box0, const Math::Box3& box1);
        static Math::Box3 computeAlignedBox(const std::vector<Math::Vector3>& pos);
        static Math::Box3 computeAlignedBox(const std::vector<Math::Vector4>& pos);
        static Math::Box3 computeAlignedBox(const float* vert, unsigned pitch, unsigned quantity);

        static Math::Box3 computeOrientedBox(const std::vector<Math::Vector3>& pos);
        static Math::Box3 computeOrientedBox(const std::vector<Math::Vector4>& pos4);
        static Math::Box3 computeOrientedBox(const float* vert, unsigned int pitch, unsigned int quantity);
    };
}

#endif // CONTAINMENT_BOX3_HPP

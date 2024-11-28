/*********************************************************************
 * \file   QuaternionDecompose.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef QUATERNION_DECOMPOSE_HPP
#define QUATERNION_DECOMPOSE_HPP
#include "Quaternion.hpp"
namespace Math
{
    class Vector3;
    struct QuaternionDecompose
    {
        Quaternion m_swing;
        Quaternion m_twist;
    };

    /** Compute a quaternion that rotates unit-length vector V1 to unit-length
     vector V2.  The rotation is about the axis perpendicular to both V1 and
     V2, with angle of that between V1 and V2.  If V1 and V2 are parallel,
     any axis of rotation will do, such as the permutation (z2,x2,y2), where
     V2 = (x2,y2,z2). */
    Quaternion align(const Vector3& vec1, const Vector3& vec2);

    /** Decompose a quaternion into q = q_twist * q_swing, where q is 'this'
     quaternion.  If V1 is the input axis and V2 is the rotation of V1 by
     q, q_swing represents the rotation about the axis perpendicular to
     V1 and V2 (see Quaternion::Align), and q_twist is a rotation about V1. */
    QuaternionDecompose decomposeTwistTimesSwing(const Quaternion& q, const Vector3& vec1);

    /** Decompose a quaternion into q = q_swing * q_twist, where q is 'this'
     quaternion.  If V1 is the input axis and V2 is the rotation of V1 by
     q, q_swing represents the rotation about the axis perpendicular to
     V1 and V2 (see Quaternion::Align), and q_twist is a rotation about V1. */
    QuaternionDecompose decomposeSwingTimesTwist(const Quaternion& q, const Vector3& vec1);
}

#endif // QUATERNION_DECOMPOSE_HPP

﻿/*********************************************************************
 * \file   Plane3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef PLANE3_HPP
#define PLANE3_HPP
#include "Vector3.hpp"

namespace Math
{
    /** Math Lib Plane3
    @remarks
    The plane is represented as dot(N,X) = c where N is a unit-length
    normal vector, c is the plane constant, and X is any point on the
    plane.
    */
    class Plane3
    {
    public:
        enum class SideOfPlane : std::int8_t
        {
            Negative = -1,
            Overlap = 0,
            Positive = 1,
        };
    public:
        Plane3();
        /** specify N and c directly */
        Plane3(const Vector3& normal, float constant);
        /** N is specified, c = dot(N,P) where P is on the plane */
        Plane3(const Vector3& normal, const Vector3& p);
        /** N = cross(P1-P0,P2-P0)/length(cross(P1-P0,P2-P0)), c = dot(N,P0) where
         P0, P1, P2 are points on the plane. */
        Plane3(const Vector3& p0, const Vector3& p1, const Vector3& p2);

        [[nodiscard]] Vector3 normal() const;
        void normal(const Vector3& normal);
        [[nodiscard]] float constant() const;
        void constant(float c);

        bool operator== (const Plane3& plane) const; ///< 浮點數值比較
        bool operator!= (const Plane3& plane) const;    ///< 浮點數值比較

        /** side classify
        @remarks
         The "positive side" of the plane is the half space to which the plane
         normal points.  The "negative side" is the other half space.  The
         function returns +1 for the positive side, -1 for the negative side,
         and 0 for the point being on the plane.
        */
        [[nodiscard]] SideOfPlane whichSide(const Vector3& p) const;

        /** distance to plane
        @remarks
         Compute d = dot(N,Q)-c where N is the plane normal and c is the plane
         constant.  This is a signed distance.  The sign of the return value is
         positive if the point is on the positive side of the plane, negative if
         the point is on the negative side, and zero if the point is on the
         plane.
        */
        [[nodiscard]] float distanceTo(const Vector3& q) const;

    protected:
        Vector3 m_normal;
        float m_constant;
    };
}

#endif // PLANE3_HPP

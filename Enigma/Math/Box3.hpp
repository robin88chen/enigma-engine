/*********************************************************************
 * \file   Box3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef BOX3_HPP
#define BOX3_HPP
#include "Vector3.hpp"
#include "Point3.hpp"
#include <array>
namespace Math
{
    /** Math Lib Box3
    @remarks
     A box has center C, axis directions U[0], U[1], and U[2] (all
     unit-length vectors), and extents e[0], e[1], and e[2] (all nonnegative
     numbers).  A point X = C+y[0]*U[0]+y[1]*U[1]+y[2]*U[2] is inside or
     on the box whenever |y[i]| <= e[i] for all i.
    */
    class Box3
    {
    public:
        Box3();
        Box3(const Point3& center, const std::array<Vector3, 3>& axis, const std::array<float, 3>& extent);
        Box3(const Point3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2,
            float extent0, float extent1, float extent2);

        [[nodiscard]] Point3 center() const;
        void center(const Point3& center);
        [[nodiscard]] Vector3 axis(unsigned index) const;
        [[nodiscard]] const std::array<Vector3, 3>& axis() const;
        void axis(const std::array<Vector3, 3>& axis);
        [[nodiscard]] float extent(unsigned index) const;
        [[nodiscard]] const std::array<float, 3>& extent() const;
        void extent(unsigned index, float extent);

        constexpr static unsigned VERTICES_COUNT = 8;
        /**
        @return { (-x,-y,-z),(+x,-y,-z),(+x,+y,-z),(-x,+y,-z),
        (-x,-y,+z),(+x,-y,+z),(+x,+y,+z),(-x,+y,+z) }
        */
        [[nodiscard]] std::array<Point3, VERTICES_COUNT> computeVertices() const;

        /** swap to major axis (把軸向量取最大值對齊x,y,z) */
        [[nodiscard]] Box3 swapToMajorAxis() const;

        bool operator== (const Box3& box) const; ///< 浮點數值比較
        bool operator!= (const Box3& box) const;    ///< 浮點數值比較

        [[nodiscard]] bool isZero() const;

        [[nodiscard]] bool contains(const Point3& p) const;

        static const Box3 UNIT_BOX;

    private:
        [[nodiscard]] bool isValid() const;

        Point3 m_center;
        std::array<Vector3, 3> m_axis;  ///< must be an orthonormal set of vectors
        std::array<float, 3> m_extent;         ///< must be nonnegative
    };
}

#endif // BOX3_HPP

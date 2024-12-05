/*********************************************************************
 * \file   Box2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef BOX2_HPP
#define BOX2_HPP
#include "Vector2.hpp"
#include <array>
namespace Math
{
    /** Math Lib Box2
    @remarks
    A box has center C, axis directions U[0] and U[1] (both unit-length
    vectors), and extents e[0] and e[1] (both nonnegative numbers).  A
    point X = C+y[0]*U[0]+y[1]*U[1] is inside or on the box whenever
    |y[i]| <= e[i] for all i.
    */
    class Box2
    {
    public:
        // construction
        Box2();
        Box2(const Vector2& center, const std::array<Vector2, 2>& axis, const std::array<float, 2>& extents);
        Box2(const Vector2& center, const Vector2& axis0, const Vector2& axis1, float extent0, float extent1);

        [[nodiscard]] Vector2 center() const;
        void center(const Vector2& center);
        [[nodiscard]] Vector2 axis(unsigned  index) const;
        [[nodiscard]] const std::array<Vector2, 2>& axis() const;
        void axis(const std::array<Vector2, 2>& axis);
        [[nodiscard]] float extent(unsigned index) const;
        [[nodiscard]] const std::array<float, 2>& extent() const;
        void extent(unsigned index, float extent);
        constexpr static unsigned VERTICES_COUNT = 4;
        /**
        @return { (-x,-y),(+x,-y),(+x,+y),(-x,+y) }
        */
        [[nodiscard]] std::array<Vector2, VERTICES_COUNT> computeVertices() const;

        bool operator== (const Box2& box) const; ///< 浮點數值比較
        bool operator!= (const Box2& box) const;    ///< 浮點數值比較

    private:
        [[nodiscard]] bool isValid() const;

        Vector2 m_center;
        std::array<Vector2, 2> m_axis;  ///< must be an orthonormal set of vectors
        std::array<float, 2> m_extent;         ///< must be nonnegative
    };
}

#endif // BOX2_HPP

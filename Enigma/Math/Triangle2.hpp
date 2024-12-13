/*********************************************************************
 * \file   Triangle2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef TRIANGLE2_HPP
#define TRIANGLE2_HPP
#include "Point2.hpp"
#include <array>
namespace Math
{
    /** Math Lib Triangle2
    @remarks
     The triangle is represented as an array of three vertices, V0, V1,
     and V2.
    */
    class Triangle2
    {
    public:
        Triangle2();
        Triangle2(const Point2& p0, const Point2& p1, const Point2& p2);
        explicit Triangle2(const std::array<Point2, 3>& pts);

        [[nodiscard]] Point2 point(unsigned i) const;
        void point(unsigned i, const Point2& p);

        bool operator==(const Triangle2& tri) const;
        bool operator!=(const Triangle2& tri) const;

        // distance from the point Q to the triangle
        [[nodiscard]] float distanceTo(const Point2& p) const;

    protected:
        std::array<Point2, 3> m_points;
    };
}

#endif // TRIANGLE2_HPP

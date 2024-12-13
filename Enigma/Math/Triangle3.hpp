/*********************************************************************
 * \file   Triangle3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef TRIANGLE3_HPP
#define TRIANGLE3_HPP
#include "Point3.hpp"
#include <array>
namespace Math
{
    /** Math Lib Triangle3
    @remarks
    The triangle is represented as an array of three vertices, V0, V1,
    and V2.
    */
    class Triangle3
    {
    public:
        Triangle3();
        Triangle3(const Point3& p0, const Point3& p1, const Point3& p2);
        explicit Triangle3(const std::array<Point3, 3>& pts);

        [[nodiscard]] Point3 point(int i) const;
        void point(unsigned i, const Point3& p);

        bool operator== (const Triangle3& tri) const;
        bool operator!= (const Triangle3& tri) const;

        // distance from the point Q to the triangle
        [[nodiscard]] float distanceTo(const Point3& q) const;

    protected:
        std::array<Point3, 3> m_points;
    };

}

#endif // TRIANGLE3_HPP

/*********************************************************************
 * \file   Sphere2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef SPHERE2_HPP
#define SPHERE2_HPP
#include "Point2.hpp"

namespace Math
{
    /** Math Lib Sphere2
    @remarks
        The sphere (circle) is represented as |X-C| = R where C is the center and R is
        the radius.
    */
    class Sphere2
    {
    public:
        Sphere2();
        Sphere2(const Point2& center, float radius);

        [[nodiscard]] Point2 center() const;
        void center(const Point2& center);
        [[nodiscard]] float radius() const;
        void radius(float radius);

        bool operator== (const Sphere2& sphere) const; ///< 浮點數值比較
        bool operator!= (const Sphere2& sphere) const;  ///< 浮點數值比較

        bool contains(const Point2& point) const; ///< 是否包含點
    private:
        Point2 m_center;
        float m_radius;
    };
}

#endif // SPHERE2_HPP

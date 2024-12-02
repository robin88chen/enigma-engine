/*********************************************************************
 * \file   Sphere2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef SPHERE2_HPP
#define SPHERE2_HPP
#include "Vector2.hpp"

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
        Sphere2(const Vector2& center, float radius);

        [[nodiscard]] Vector2 center() const;
        void center(const Vector2& center);
        [[nodiscard]] float radius() const;
        void radius(float radius);

        bool operator== (const Sphere2& sphere) const; ///< 浮點數值比較
        bool operator!= (const Sphere2& sphere) const;  ///< 浮點數值比較

    private:
        Vector2 m_center;
        float m_radius;
    };
}

#endif // SPHERE2_HPP

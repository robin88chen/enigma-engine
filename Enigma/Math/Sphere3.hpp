/*********************************************************************
 * \file   Sphere3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef SPHERE3_HPP
#define SPHERE3_HPP
#include "Point3.hpp"

namespace Math
{
    /** Math Lib Sphere3
    @remarks
     The sphere is represented as |X-C| = R where C is the center and R is
     the radius.
    */
    class Sphere3
    {
    public:
        Sphere3();
        Sphere3(const Point3& center, float radius);

        [[nodiscard]] Point3 center() const;
        void center(const Point3& center);
        [[nodiscard]] float radius() const;
        void radius(float radius);

        bool operator== (const Sphere3& sphere) const; ///< 浮點數值比較
        bool operator!= (const Sphere3& sphere) const;  ///< 浮點數值比較

        [[nodiscard]] bool isEmpty() const;
        static const Sphere3 UNIT_SPHERE;

    private:
        Point3 m_center;
        float m_radius;
    };
}

#endif // SPHERE3_HPP

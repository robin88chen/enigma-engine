/*********************************************************************
 * \file   Ray2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef RAY2_HPP
#define RAY2_HPP
#include "Vector2.hpp"
#include "Point2.hpp"

namespace Math
{
    /** Math Lib Ray2
    @remarks
     The ray is represented as P+t*D, where P is the ray origin, D is a
     unit-length direction vector, and t >= 0.  The user must ensure that
     the direction vector satisfies this condition.
    */
    class Ray2
    {
    public:
        Ray2();
        Ray2(const Point2& origin, const Vector2& direction);

        [[nodiscard]] Point2 origin() const;
        void origin(const Point2& origin);
        [[nodiscard]] Vector2 direction() const;
        void direction(const Vector2& direction);

        bool operator== (const Ray2& ray) const;    ///< 浮點數值比較
        bool operator!= (const Ray2& ray) const;    ///< 浮點數值比較

    private:
        Point2 m_origin;
        Vector2 m_direction;
    };
}

#endif // RAY2_HPP

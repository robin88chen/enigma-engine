/*********************************************************************
 * \file   Ray3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef RAY3_HPP
#define RAY3_HPP
#include "Vector3.hpp"

namespace Math
{
    /** Math Lib Ray3
    @remarks
    The ray is represented as P+t*D, where P is the ray origin, D is a
    unit-length direction vector, and t >= 0.  The user must ensure that
    the direction vector satisfies this condition.
    */
    class Ray3
    {
    public:
        Ray3();
        Ray3(const Vector3& origin, const Vector3& direction);

        [[nodiscard]] Vector3 origin() const;
        void origin(const Vector3& origin);
        [[nodiscard]] Vector3 direction() const;
        void direction(const Vector3& direction);

        bool operator== (const Ray3& ray) const;    ///< 浮點數值比較
        bool operator!= (const Ray3& ray) const;    ///< 浮點數值比較

    private:
        Vector3 m_origin;
        Vector3 m_direction;
    };
}

#endif // RAY3_HPP

/*********************************************************************
 * \file   Line3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef LINE3_HPP
#define LINE3_HPP
#include "Vector3.hpp"
namespace Math
{
    /** Math Lib Line3
    @remarks
    The line is represented as P+t*D where P is the line origin and D is
    a unit-length direction vector.
    */
    class Line3
    {
    public:
        Line3();
        Line3(const Vector3& origin, const Vector3& direction);

        [[nodiscard]] Vector3 origin() const;
        void origin(const Vector3& origin);
        [[nodiscard]] Vector3 direction() const;
        void direction(const Vector3& direction);

        bool operator== (const Line3& line) const; ///< 浮點數值比較
        bool operator!= (const Line3& line) const;  ///< 浮點數值比較

    private:
        Vector3 m_origin;
        Vector3 m_direction;
    };
}

#endif // LINE3_HPP

/*********************************************************************
 * \file   Line2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef LINE2_HPP
#define LINE2_HPP
#include "Vector2.hpp"
#include "Point2.hpp"

namespace Math
{
    /** Math Lib Line2
    @remarks
     The line is represented as P+t*D where P is the line origin and D is
     a unit-length direction vector.
     */
    class Line2
    {
    public:
        Line2();
        Line2(const Point2& origin, const Vector2& direction);

        [[nodiscard]] Point2 origin() const;
        void origin(const Point2& origin);
        [[nodiscard]] Vector2 direction() const;
        void direction(const Vector2& direction);

        bool operator== (const Line2& line) const; ///< 浮點數值比較
        bool operator!= (const Line2& line) const;  ///< 浮點數值比較

    private:
        Point2 m_origin;
        Vector2 m_direction;
    };
}

#endif // LINE2_HPP

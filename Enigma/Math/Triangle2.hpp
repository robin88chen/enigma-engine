/*********************************************************************
 * \file   Triangle2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef TRIANGLE2_HPP
#define TRIANGLE2_HPP
#include "Vector2.hpp"
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
        Triangle2(const Vector2& vec0, const Vector2& vec1, const Vector2& vec2);
        explicit Triangle2(const std::array<Vector2, 3>& vec);

        [[nodiscard]] Vector2 vector(unsigned i) const;
        void vector(unsigned i, const Vector2& vec);

        bool operator==(const Triangle2& tri) const;
        bool operator!=(const Triangle2& tri) const;

        // distance from the point Q to the triangle
        [[nodiscard]] float distanceTo(const Vector2& vec) const;

    protected:
        std::array<Vector2, 3> m_vec;
    };
}

#endif // TRIANGLE2_HPP

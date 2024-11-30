/*********************************************************************
 * \file   Triangle3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef TRIANGLE3_HPP
#define TRIANGLE3_HPP
#include "Vector3.hpp"
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
        Triangle3(const Vector3& vec0, const Vector3& vec1, const Vector3& vec2);
        explicit Triangle3(const std::array<Vector3, 3>& vec);

        [[nodiscard]] Vector3 vector(int i) const;
        void vector(unsigned i, const Vector3& vec);

        bool operator== (const Triangle3& tri) const;
        bool operator!= (const Triangle3& tri) const;

        // distance from the point Q to the triangle
        [[nodiscard]] float distanceTo(const Vector3& vec) const;

    protected:
        std::array<Vector3, 3> m_vec;
    };

}

#endif // TRIANGLE3_HPP

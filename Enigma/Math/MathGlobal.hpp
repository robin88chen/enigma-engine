/*********************************************************************
 * \file   MathGlobal.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef MATH_GLOBAL_HPP
#define MATH_GLOBAL_HPP

#include <limits>

namespace Math
{
    class FloatCompare
    {
    public:
        [[nodiscard]] static bool isEqual(float l, float r);
        [[nodiscard]] static float epsilonUlp();  ///< 修正 epsilon 誤差的放大倍數, 預設為 1.0f
        static void epsilonUlp(float epsilon);
        static constexpr float ZERO_TOLERANCE = std::numeric_limits<float>::epsilon();  ///< =10e-6

    private:
        static float m_epsilonUlp;
    };
    class Constants
    {
    public:
        static const float PI;
        static const float HALF_PI;
    };
}

#endif // MATH_GLOBAL_HPP

/*********************************************************************
 * \file   MathGlobal.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef MATH_GLOBAL_HPP
#define MATH_GLOBAL_HPP

namespace Math
{
    class FloatCompare
    {
    public:
        [[nodiscard]] static bool isEqual(float l, float r);
        [[nodiscard]] static float epsilonUlp();  ///< 修正 epsilon 誤差的放大倍數, 預設為 1.0f
        static void epsilonUlp(float epsilon);
        static float zeroTolerance();  ///< =1e-6 * epsilonUlp()

    private:
        static float m_epsilonUlp;
        static float m_zeroTolerance;
    };
    class Constants
    {
    public:
        static const float PI;
        static const float HALF_PI;
        static const float MAX_FLOAT;
    };
}

#endif // MATH_GLOBAL_HPP

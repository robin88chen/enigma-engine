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
    bool isEqual(float l, float r);
    static float g_epsilon_ulp = 1.0f;  ///< 修正 epsilon 誤差的放大倍數, 預設為 1.0f
    static constexpr float ZERO_TOLERANCE = std::numeric_limits<float>::epsilon();  ///< =10e-6
}

#endif // MATH_GLOBAL_HPP

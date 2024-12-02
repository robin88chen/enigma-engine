/*********************************************************************
 * \file   Dimension.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef DIMENSION_HPP
#define DIMENSION_HPP
#include "MathGlobal.hpp"
#include <type_traits>

namespace Math
{
    template<typename T, typename = std::enable_if_t<std::is_scalar_v<T>, T>> struct Dimension
    {
        T m_width;
        T m_height;
        bool isEqual(T a, T b, std::enable_if_t<std::is_integral_v<T> >* /*unused*/ = nullptr)
        {
            return a == b;
        }
        bool isEqual(T a, T b, std::enable_if_t<std::is_floating_point_v<T> >* /*unused*/ = nullptr)
        {
            return FloatCompare::isEqual(a, b);
        }
        bool operator==(const Dimension& rhs) const
        {
            return isEqual(m_width, rhs.m_width) && isEqual(m_height, rhs.m_height);
        }
        bool operator!=(const Dimension& rhs) const
        {
            return !(*this == rhs);
        }
    };
}

#endif // DIMENSION_HPP

/*********************************************************************
 * \file   Rectangle.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "MathGlobal.hpp"
#include <type_traits>
namespace Math
{
    template<typename T, typename = std::enable_if_t<std::is_scalar_v<T>, T>> class Rectangle
    {
    public:
        Rectangle() = default;
        Rectangle(T left, T top, T right, T bottom) : m_left(left), m_top(top), m_right(right), m_bottom(bottom) {};
        bool operator== (const Rectangle& rect) const
        {
            return isEqual(m_left, rect.m_left) && isZero(m_top, rect.m_top) && isEqual(m_right, rect.m_right) && isEqual(m_bottom, rect.m_bottom);
        }
        bool operator!= (const Rectangle& rect) const
        {
            return !(*this == rect);
        }
        [[nodiscard]] bool isZero() const
        {
            return isZero(m_left) && isZero(m_top) && isZero(m_right) && isZero(m_bottom);
        }
        T left() const
        {
            return m_left;
        }
        void left(T left)
        {
            m_left = left;
        }
        T top() const
        {
            return m_top;
        }
        void top(T top)
        {
            m_top = top;
        }
        T right() const
        {
            return m_right;
        }
        void right(T right)
        {
            m_right = right;
        }
        T bottom() const
        {
            return m_bottom;
        }
        void bottom(T bottom)
        {
            m_bottom = bottom;
        }
        T width() const
        {
            return m_right - m_left;
        }
        T height() const
        {
            return m_bottom - m_top;
        }
    private:
        bool isEqual(T a, T b, std::enable_if_t<std::is_integral_v<T> >* /*unused*/ = nullptr)
        {
            return a == b;
        }
        bool isEqual(T a, T b, std::enable_if_t<std::is_floating_point_v<T> >* /*unused*/ = nullptr)
        {
            return FloatCompare::isEqual(a, b);
        }
        bool isZero(T a, std::enable_if_t<std::is_integral_v<T> >* /*unused*/ = nullptr)
        {
            return a == 0;
        }
        bool isZero(T a, std::enable_if_t<std::is_floating_point_v<T> >* /*unused*/ = nullptr)
        {
            return FloatCompare::isEqual(a, 0.0f);
        }

        T m_left;
        T m_top;
        T m_right;
        T m_bottom;
    };
}

#endif // RECTANGLE_HPP

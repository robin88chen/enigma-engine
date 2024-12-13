/*********************************************************************
 * \file   Point2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef POINT2_HPP
#define POINT2_HPP

namespace Math
{
    class Vector2;
    class Point2
    {
    public:
        Point2();
        Point2(float x, float y);

        bool operator==(const Point2& p) const;
        bool operator!=(const Point2& p) const;

        [[nodiscard]] float x() const;
        void x(float x);
        [[nodiscard]] float y() const;
        void y(float y);

        Point2 operator+(const Point2& p) const;
        Point2 operator+(const Vector2& v) const;
        Vector2 operator-(const Point2& p) const;
        Point2 operator* (float scalar) const;
        Point2 operator/ (float scalar) const;
        Point2 operator- () const;

        Point2& operator+= (const Point2& p);
        Point2& operator+= (const Vector2& v);

        static const Point2 ZERO;
    private:
        float m_x;
        float m_y;
    };
    Point2 operator* (float scalar, const Point2& p);
}

#endif // POINT2_HPP

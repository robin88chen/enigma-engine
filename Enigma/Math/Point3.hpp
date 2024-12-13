/*********************************************************************
 * \file   Point3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef POINT3_HPP
#define POINT3_HPP

namespace Math
{
    class Vector3;
    class Point3
    {
    public:
        Point3();
        Point3(float x, float y, float z);

        bool operator==(const Point3& p) const;
        bool operator!=(const Point3& p) const;

        [[nodiscard]] float x() const;
        void x(float x);
        [[nodiscard]] float y() const;
        void y(float y);
        [[nodiscard]] float z() const;
        void z(float z);

        Point3 operator+(const Point3& p) const;
        Point3 operator+(const Vector3& v) const;
        Vector3 operator-(const Point3& p) const;
        Point3 operator* (float scalar) const;
        Point3 operator/ (float scalar) const;
        Point3 operator- () const;

        Point3& operator+= (const Point3& p);
        Point3& operator+= (const Vector3& v);

        static const Point3 ZERO;
    private:
        float m_x;
        float m_y;
        float m_z;
    };
    Point3 operator* (float scalar, const Point3& p);
}

#endif // POINT3_HPP

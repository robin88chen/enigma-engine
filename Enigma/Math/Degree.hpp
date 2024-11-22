/*********************************************************************
 * \file   Degree.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef DEGREE_HPP
#define DEGREE_HPP

namespace Math
{
    class Radian;
    class Degree
    {
    public:
        Degree() : m_degree(0.0f) {}
        explicit Degree(float degree) : m_degree(degree) {}

        Degree operator+(const Degree& other) const;
        Degree operator-(const Degree& other) const;
        Degree operator*(float scalar) const;
        Degree operator/(float scalar) const;

        Degree& operator+=(const Degree& other);
        Degree& operator-=(const Degree& other);
        Degree& operator*=(float scalar);
        Degree& operator/=(float scalar);

        bool operator==(const Degree& other) const;
        bool operator!=(const Degree& other) const;
        bool operator<(const Degree& other) const;
        bool operator>(const Degree& other) const;
        bool operator<=(const Degree& other) const;
        bool operator>=(const Degree& other) const;

        [[nodiscard]] float value() const { return m_degree; }
        [[nodiscard]] Radian radian() const;

    private:
        float m_degree;
    };
}

#endif // DEGREE_HPP

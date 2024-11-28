/*********************************************************************
 * \file   Radian.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef RADIAN_HPP
#define RADIAN_HPP

namespace Math
{
    class Degree;

    class Radian
    {
    public:
        Radian() : m_radian(0.0f) {}
        explicit Radian(float radian) : m_radian(radian) {}

        Radian operator+(const Radian& other) const;
        Radian operator-(const Radian& other) const;
        Radian operator*(float scalar) const;
        Radian operator/(float scalar) const;

        Radian& operator+=(const Radian& other);
        Radian& operator-=(const Radian& other);
        Radian& operator*=(float scalar);
        Radian& operator/=(float scalar);

        bool operator==(const Radian& other) const;
        bool operator!=(const Radian& other) const;
        bool operator<(const Radian& other) const;
        bool operator>(const Radian& other) const;
        bool operator<=(const Radian& other) const;
        bool operator>=(const Radian& other) const;

        [[nodiscard]] float value() const { return m_radian; }
        [[nodiscard]] Degree degree() const;

        static const Radian ZERO;
    private:
        float m_radian;
    };

    Radian operator* (float scale, const Radian& radian);
}

#endif // RADIAN_HPP

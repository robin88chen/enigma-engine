#include "Degree.hpp"
#include "MathGlobal.hpp"
#include "Radian.hpp"
#include <cassert>

using namespace Math;

Degree Degree::operator+(const Degree& other) const
{
    return Degree{ m_degree + other.m_degree };
}

Degree Degree::operator-(const Degree& other) const
{
    return Degree{ m_degree - other.m_degree };
}

Degree Degree::operator*(float scalar) const
{
    return Degree{ m_degree * scalar };
}

Degree Degree::operator/(float scalar) const
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    return Degree{ m_degree / scalar };
}

Degree Degree::operator-() const
{
    return Degree{ -m_degree };
}

Degree& Degree::operator+=(const Degree& other)
{
    m_degree += other.m_degree;
    return *this;
}

Degree& Degree::operator-=(const Degree& other)
{
    m_degree -= other.m_degree;
    return *this;
}

Degree& Degree::operator*=(float scalar)
{
    m_degree *= scalar;
    return *this;
}

Degree& Degree::operator/=(float scalar)
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    m_degree /= scalar;
    return *this;
}

bool Degree::operator==(const Degree& other) const
{
    return FloatCompare::isEqual(m_degree, other.m_degree);
}

bool Degree::operator!=(const Degree& other) const
{
    return !FloatCompare::isEqual(m_degree, other.m_degree);
}

bool Degree::operator<(const Degree& other) const
{
    return m_degree < other.m_degree;
}

bool Degree::operator>(const Degree& other) const
{
    return m_degree > other.m_degree;
}

bool Degree::operator<=(const Degree& other) const
{
    return m_degree <= other.m_degree;
}

bool Degree::operator>=(const Degree& other) const
{
    return m_degree >= other.m_degree;
}

const Degree Degree::ZERO{ 0.0f };

Radian Degree::radian() const
{
    static const float deg_to_rad = Constants::PI / 180.0f;
    return Radian{ m_degree * deg_to_rad };
}

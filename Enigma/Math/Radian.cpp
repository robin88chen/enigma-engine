#include "Radian.hpp"
#include "Degree.hpp"
#include "MathGlobal.hpp"
#include <cassert>

using namespace Math;

Radian Radian::operator+(const Radian& other) const
{
    return Radian{ m_radian + other.m_radian };
}

Radian Radian::operator-(const Radian& other) const
{
    return Radian{ m_radian - other.m_radian };
}

Radian Radian::operator*(float scalar) const
{
    return Radian{ m_radian * scalar };
}

Radian Radian::operator/(float scalar) const
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    return Radian{ m_radian / scalar };
}

Radian& Radian::operator+=(const Radian& other)
{
    m_radian += other.m_radian;
    return *this;
}

Radian& Radian::operator-=(const Radian& other)
{
    m_radian -= other.m_radian;
    return *this;
}

Radian& Radian::operator*=(float scalar)
{
    m_radian *= scalar;
    return *this;
}

Radian& Radian::operator/=(float scalar)
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    m_radian /= scalar;
    return *this;
}

bool Radian::operator==(const Radian& other) const
{
    return FloatCompare::isEqual(m_radian, other.m_radian);
}

bool Radian::operator!=(const Radian& other) const
{
    return !FloatCompare::isEqual(m_radian, other.m_radian);
}

bool Radian::operator<(const Radian& other) const
{
    return m_radian < other.m_radian;
}

bool Radian::operator>(const Radian& other) const
{
    return m_radian > other.m_radian;
}

bool Radian::operator<=(const Radian& other) const
{
    return m_radian <= other.m_radian;
}

bool Radian::operator>=(const Radian& other) const
{
    return m_radian >= other.m_radian;
}

Degree Radian::degree() const
{
    static const float rad_to_deg = 180.0f / Constants::PI;
    return Degree{ m_radian * rad_to_deg };
}

const Radian Radian::ZERO{ 0.0f };

namespace Math
{
    Radian operator*(float scale, const Radian& radian)
    {
        return Radian{ scale * radian.value() };
    }
}

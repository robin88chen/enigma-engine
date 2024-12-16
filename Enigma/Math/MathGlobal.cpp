#include "MathGlobal.hpp"
#include <cmath>
#include <limits>

using namespace Math;

constexpr float EPSILON = 1.0e-6f;  // epsilon 用固定數值
float FloatCompare::m_epsilonUlp = 1.0f;
float FloatCompare::m_zeroTolerance = EPSILON;

float FloatCompare::epsilonUlp()
{
    return m_epsilonUlp;
}

void FloatCompare::epsilonUlp(float epsilon)
{
    m_epsilonUlp = epsilon;
    m_zeroTolerance = EPSILON * m_epsilonUlp;
}

bool FloatCompare::isEqual(float l, float r)
{
    const float diff = std::abs(l - r);
    if (diff <= zeroTolerance()) return true;
    // code from
    // https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon

    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return (diff <= tolerance(l, r))
        // unless the result is subnormal
        || (diff < std::numeric_limits<float>::min());
}

float FloatCompare::tolerance(float l, float r)
{
    return zeroTolerance() * std::abs(l + r);
}

float FloatCompare::zeroTolerance()
{
    return m_zeroTolerance;
}

const float Math::Constants::PI = 4.0f * std::atan(1.0f);
const float Math::Constants::HALF_PI = 0.5f * Constants::PI;
const float Math::Constants::MAX_FLOAT = std::numeric_limits<float>::max();

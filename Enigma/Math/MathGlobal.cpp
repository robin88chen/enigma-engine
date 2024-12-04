#include "MathGlobal.hpp"
#include <cmath>
#include <limits>

using namespace Math;

float FloatCompare::m_epsilonUlp = 1.0f;

float FloatCompare::epsilonUlp()
{
    return m_epsilonUlp;
}

void FloatCompare::epsilonUlp(float epsilon)
{
    m_epsilonUlp = epsilon;
}

bool FloatCompare::isEqual(float l, float r)
{
    const float diff = std::fabs(l - r);
    if (diff <= ZERO_TOLERANCE * m_epsilonUlp) return true;
    // code from
    // https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon

    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return (diff <= ZERO_TOLERANCE * std::fabs(l + r) * m_epsilonUlp)
        // unless the result is subnormal
        || (diff < std::numeric_limits<float>::min());
}

const float Math::Constants::PI = 4.0f * std::atan(1.0f);
const float Math::Constants::HALF_PI = 0.5f * Constants::PI;
const float Math::Constants::MAX_FLOAT = std::numeric_limits<float>::max();

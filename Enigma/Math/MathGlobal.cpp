#include "MathGlobal.hpp"
#include <cmath>

namespace Math
{
    bool isEqual(float l, float r)
    {
        const float diff = fabs(l - r);
        if (diff <= ZERO_TOLERANCE * g_epsilon_ulp) return true;
        // code from
        // https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon

        // the machine epsilon has to be scaled to the magnitude of the values used
        // and multiplied by the desired precision in ULPs (units in the last place)
        return (diff <= ZERO_TOLERANCE * std::fabs(l + r) * g_epsilon_ulp)
            // unless the result is subnormal
            || (diff < std::numeric_limits<float>::min());
    }
}

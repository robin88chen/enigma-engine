/*********************************************************************
 * \file   EulerAngles.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef EULER_ANGLES_HPP
#define EULER_ANGLES_HPP

#include "Radian.hpp"

namespace Math
{
    struct EulerAngles
    {
        Radian m_x;
        Radian m_y;
        Radian m_z;
    };
}

#endif // EULER_ANGLES_HPP

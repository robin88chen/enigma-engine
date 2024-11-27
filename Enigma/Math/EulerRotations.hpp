/*********************************************************************
 * \file   EulerRotations.hpp
 * \brief  ADR : 從 Matrix3 中移出
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef EULER_ROTATIONS_HPP
#define EULER_ROTATIONS_HPP

#include "EulerAngles.hpp"

namespace Math
{
    class Matrix3;

    /** @name Euler Angle Rotation
     @remark
     The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
     where yaw is rotation about the Up vector, pitch is rotation about the
     Right axis, and roll is rotation about the Direction axis.
     @par
      the rotation is roll first, then pitch, and finally yaw. for example,
        FromEulerAnglesXYZ is roll against Z-axis first, then pitch against Y-axis,
        and finally yaw against X-axis.
    */
    //@{
    static Matrix3 fromEulerAnglesXyz(const EulerAngles& angles);
    static Matrix3 fromEulerAnglesXzy(const EulerAngles& angles);
    static Matrix3 fromEulerAnglesYxz(const EulerAngles& angles);
    static Matrix3 fromEulerAnglesYzx(const EulerAngles& angles);
    static Matrix3 fromEulerAnglesZxy(const EulerAngles& angles);
    static Matrix3 fromEulerAnglesZyx(const EulerAngles& angles);
    [[nodiscard]] EulerAngles toEulerAnglesXyz(const Matrix3& mx);
    [[nodiscard]] EulerAngles toEulerAnglesXzy(const Matrix3& mx);
    [[nodiscard]] EulerAngles toEulerAnglesYxz(const Matrix3& mx);
    [[nodiscard]] EulerAngles toEulerAnglesYzx(const Matrix3& mx);
    [[nodiscard]] EulerAngles toEulerAnglesZxy(const Matrix3& mx);
    [[nodiscard]] EulerAngles toEulerAnglesZyx(const Matrix3& mx);
    //@}
}

#endif // EULER_ROTATIONS_HPP

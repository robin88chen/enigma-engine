#include "EulerRotations.hpp"
#include "Matrix3.hpp"
#include "MathGlobal.hpp"
#include <cmath>

namespace Math
{
    Matrix3 fromEulerAnglesXyz(const EulerAngles& angles)
    {
        return Matrix3::rotationX(angles.m_x) * Matrix3::rotationY(angles.m_y) * Matrix3::rotationZ(angles.m_z);
    }

    Matrix3 fromEulerAnglesXzy(const EulerAngles& angles)
    {
        return Matrix3::rotationX(angles.m_x) * Matrix3::rotationZ(angles.m_z) * Matrix3::rotationY(angles.m_y);
    }

    Matrix3 fromEulerAnglesYxz(const EulerAngles& angles)
    {
        return Matrix3::rotationY(angles.m_y) * Matrix3::rotationX(angles.m_x) * Matrix3::rotationZ(angles.m_z);
    }

    Matrix3 fromEulerAnglesYzx(const EulerAngles& angles)
    {
        return Matrix3::rotationY(angles.m_y) * Matrix3::rotationZ(angles.m_z) * Matrix3::rotationX(angles.m_x);
    }

    Matrix3 fromEulerAnglesZxy(const EulerAngles& angles)
    {
        return Matrix3::rotationZ(angles.m_z) * Matrix3::rotationX(angles.m_x) * Matrix3::rotationY(angles.m_y);
    }

    Matrix3 fromEulerAnglesZyx(const EulerAngles& angles)
    {
        return Matrix3::rotationZ(angles.m_z) * Matrix3::rotationY(angles.m_y) * Matrix3::rotationX(angles.m_x);
    }

    EulerAngles toEulerAnglesXyz(const Matrix3& mx)
    {
        // rot =  cy*cz          -cy*sz           sy
        //        cz*sx*sy+cx*sz  cx*cz-sx*sy*sz -cy*sx
        //       -cx*cz*sy+sx*sz  cz*sx+cx*sy*sz  cx*cy
        if (mx[0][2] < 1.0f)
        {
            if (mx[0][2] > -1.0f)
            {
                const float x_angle = std::atan2(-mx[1][2], mx[2][2]);
                const float y_angle = std::asin(mx[0][2]);
                const float z_angle = std::atan2(-mx[0][1], mx[0][0]);
                return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
            }
            // WARNING.  Not unique.  XA - ZA = -atan2(r10,r11)
            const float x_angle = -atan2(mx[1][0], mx[1][1]);
            const float y_angle = -Constants::HALF_PI;
            return { Radian(x_angle), Radian(y_angle), Radian::ZERO };
        }
        // WARNING.  Not unique.  XAngle + ZAngle = atan2(r10,r11)
        const float x_angle = atan2(mx[1][0], mx[1][1]);
        const float y_angle = Constants::HALF_PI;
        return { Radian(x_angle), Radian(y_angle), Radian::ZERO };
    }

    EulerAngles toEulerAnglesXzy(const Matrix3& mx)
    {
        // rot =  cy*cz          -sz              cz*sy
        //        sx*sy+cx*cy*sz cx*cz          -cy*sx+cx*sy*sz
        //       -cx*sy+cy*sx*sz cz*sx           cx*cy+sx*sy*sz
        if (mx[0][1] < 1.0f)
        {
            if (mx[0][1] > -1.0f)
            {
                const float x_angle = std::atan2(mx[2][1], mx[1][1]);
                const float z_angle = std::asin(-mx[0][1]);
                const float y_angle = std::atan2(mx[0][2], mx[0][0]);
                return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
            }
            // WARNING.  Not unique.  XA - ZA = -atan2(r20,r22)
            const float x_angle = -std::atan2(mx[2][0], mx[2][2]);
            const float z_angle = Constants::HALF_PI;
            return { Radian(x_angle), Radian::ZERO, Radian(z_angle) };
        }
        // WARNING.  Not unique.  XA + ZA = atan2(r20,r22)
        const float x_angle = std::atan2(mx[2][0], mx[2][2]);
        const float z_angle = -Constants::HALF_PI;
        return { Radian(x_angle), Radian::ZERO, Radian(z_angle) };
    }

    EulerAngles toEulerAnglesYxz(const Matrix3& mx)
    {
        // rot =  cy*cz+sx*sy*sz  cz*sx*sy-cy*sz  cx*sy
        //        cx*sz           cx*cz          -sx
        //       -cz*sy+cy*sx*sz  cy*cz*sx+sy*sz  cx*cy
        if (mx[1][2] < 1.0f)
        {
            if (mx[1][2] > -1.0f)
            {
                const float y_angle = std::atan2(mx[0][2], mx[2][2]);
                const float x_angle = std::asin(-mx[1][2]);
                const float z_angle = std::atan2(mx[1][0], mx[1][1]);
                return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
            }
            // WARNING.  Not unique.  YA - ZA = atan2(r01,r00)
            const float y_angle = std::atan2(mx[0][1], mx[0][0]);
            const float x_angle = Constants::HALF_PI;
            return { Radian(x_angle), Radian(y_angle), Radian::ZERO };
        }
        // WARNING.  Not unique.  YA + ZA = atan2(-r01,r00)
        const float y_angle = std::atan2(-mx[0][1], mx[0][0]);
        const float x_angle = -Constants::HALF_PI;
        return { Radian(x_angle), Radian(y_angle), Radian::ZERO };
    }

    EulerAngles toEulerAnglesYzx(const Matrix3& mx)
    {
        // rot =  cy*cz           sx*sy-cx*cy*sz  cx*sy+cy*sx*sz
        //        sz              cx*cz          -cz*sx
        //       -cz*sy           cy*sx+cx*sy*sz  cx*cy-sx*sy*sz
        if (mx[1][0] < 1.0f)
        {
            if (mx[1][0] > -1.0f)
            {
                const float y_angle = std::atan2(-mx[2][0], mx[0][0]);
                const float z_angle = std::asin(mx[1][0]);
                const float x_angle = std::atan2(-mx[1][2], mx[1][1]);
                return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
            }
            // WARNING.  Not unique.  YA - XA = -atan2(r21,r22);
            const float y_angle = -std::atan2(mx[2][1], mx[2][2]);
            const float z_angle = -Constants::HALF_PI;
            return { Radian::ZERO, Radian(y_angle), Radian(z_angle) };
        }
        // WARNING.  Not unique.  YA + XA = atan2(r21,r22)
        const float y_angle = std::atan2(mx[2][1], mx[2][2]);
        const float z_angle = Constants::HALF_PI;
        return { Radian::ZERO, Radian(y_angle), Radian(z_angle) };
    }

    EulerAngles toEulerAnglesZxy(const Matrix3& mx)
    {
        // rot =  cy*cz-sx*sy*sz -cx*sz          cz*sy+cy*sx*sz
        //        cz*sx*sy+cy*sz  cx*cz          -cy*cz*sx+sy*sz
        //       -cx*sy           sx              cx*cy
        if (mx[2][1] < 1.0f)
        {
            if (mx[2][1] > -1.0f)
            {
                const float z_angle = std::atan2(-mx[0][1], mx[1][1]);
                const float x_angle = std::asin(mx[2][1]);
                const float y_angle = std::atan2(-mx[2][0], mx[2][2]);
                return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
            }
            // WARNING.  Not unique.  ZA - XA = -atan2(r12,r10)
            const float z_angle = -std::atan2(mx[0][2], mx[0][0]);
            const float x_angle = -Constants::HALF_PI;
            return { Radian(x_angle), Radian::ZERO, Radian(z_angle) };
        }
        // WARNING.  Not unique.  ZA + XA = atan2(r12,r10)
        const float z_angle = std::atan2(mx[0][2], mx[0][0]);
        const float x_angle = Constants::HALF_PI;
        return { Radian(x_angle), Radian::ZERO, Radian(z_angle) };
    }

    EulerAngles toEulerAnglesZyx(const Matrix3& mx)
    {
        // rot =  cy*cz           cz*sx*sy-cx*sz  cx*cz*sy+sx*sz
        //        cy*sz           cx*cz+sx*sy*sz -cz*sx+cx*sy*sz
        //       -sy              cy*sx           cx*cy
        if (mx[2][0] < 1.0f)
        {
            if (mx[2][0] > -1.0f)
            {
                const float z_angle = std::atan2(mx[1][0], mx[0][0]);
                const float y_angle = std::asin(-mx[2][0]);
                const float x_angle = std::atan2(mx[2][1], mx[2][2]);
                return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
            }
            // WARNING.  Not unique.  ZA - XA = -atan2(r01,r02)
            const float z_angle = -std::atan2(mx[0][1], mx[0][2]);
            const float y_angle = Constants::HALF_PI;
            return { Radian::ZERO, Radian(y_angle), Radian(z_angle) };
        }
        // WARNING.  Not unique.  ZA + XA = atan2(-r01,-r02)
        const float z_angle = std::atan2(-mx[0][1], -mx[0][2]);
        const float y_angle = -Constants::HALF_PI;
        return { Radian::ZERO, Radian(y_angle), Radian(z_angle) };
    }

}

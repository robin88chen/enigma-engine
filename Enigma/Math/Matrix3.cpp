#include "Matrix3.hpp"
#include "MathGlobal.hpp"
#include "Matrix4.hpp"
#include "Radian.hpp"
#include "Vector3.hpp"
#include "EulerAngles.hpp"
#include "Vector2.hpp"
#include <cassert>
#include <cmath>

using namespace Math;

Matrix3::Matrix3() : m_entry{ {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} }
{
}

Matrix3::Matrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
    : m_entry{ {m00, m01, m02}, {m10, m11, m12}, {m20, m21, m22} }
{
}

// NOLINTNEXTLINE
Matrix3::Matrix3(const std::array<float, 9>& m) : m_entry{ {m[0], m[1], m[2]}, {m[3], m[4], m[5]}, {m[6], m[7], m[8]} }
{
}

Matrix3::Matrix3(const Matrix4& m) : m_entry{ {m[0][0], m[0][1], m[0][2]}, {m[1][0], m[1][1], m[1][2]}, {m[2][0], m[2][1], m[2][2]} }
{
}

Matrix3 Matrix3::makeZero()
{
    return {};
}

Matrix3 Matrix3::makeIdentity()
{
    return { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix3 Matrix3::makeDiagonal(float m00, float m11, float m22)
{
    return { m00, 0.0f, 0.0f, 0.0f, m11, 0.0f, 0.0f, 0.0f, m22 };
}

Matrix3 Matrix3::fromAxisAngle(const Vector3& axis, const Radian& angle)
{
    const float cos_value = std::cos(angle.value());
    const float sin_value = std::sin(angle.value());
    const float one_minus_cos = 1.0f - cos_value;
    const float x = axis.x();
    const float y = axis.y();
    const float z = axis.z();
    const float xty = x * y * one_minus_cos;
    const float xtz = x * z * one_minus_cos;
    const float ytz = y * z * one_minus_cos;
    const float xs = x * sin_value;
    const float ys = y * sin_value;
    const float zs = z * sin_value;
    return { x * x * one_minus_cos + cos_value, xty - zs, xtz + ys, xty + zs, y * y * one_minus_cos + cos_value, ytz - xs, xtz - ys, ytz + xs, z * z * one_minus_cos + cos_value };
}

Matrix3 Matrix3::fromRowVectors(const std::array<Vector3, 3>& rows)
{
    return { rows[0].x(), rows[0].y(), rows[0].z(), rows[1].x(), rows[1].y(), rows[1].z(), rows[2].x(), rows[2].y(), rows[2].z() };
}

Matrix3 Matrix3::fromColumnVectors(const std::array<Vector3, 3>& columns)
{
    return { columns[0].x(), columns[1].x(), columns[2].x(), columns[0].y(), columns[1].y(), columns[2].y(), columns[0].z(), columns[1].z(), columns[2].z() };
}

Matrix3::operator const float* () const
{
    return &m_entry[0][0];
}

Matrix3::operator float* ()
{
    return &m_entry[0][0];
}

const float* Matrix3::operator[] (int row) const
{
    return m_entry[row];
}

float* Matrix3::operator[] (int row)
{
    return m_entry[row];
}

float Matrix3::operator() (int row, int col) const
{
    return m_entry[row][col];
}

float& Matrix3::operator() (int row, int col)
{
    return m_entry[row][col];
}

void Matrix3::setRow(int row, const Vector3& v)
{
    assert(row <= 2);
    m_entry[row][0] = v.x();
    m_entry[row][1] = v.y();
    m_entry[row][2] = v.z();
}

Vector3 Matrix3::getRow(int row) const
{
    assert(row <= 2);
    return { m_entry[row][0], m_entry[row][1], m_entry[row][2] };
}

void Matrix3::setColumn(int col, const Vector3& v)
{
    assert(col <= 2);
    m_entry[0][col] = v.x();
    m_entry[1][col] = v.y();
    m_entry[2][col] = v.z();
}

Vector3 Matrix3::getColumn(int col) const
{
    assert(col <= 2);
    return { m_entry[0][col], m_entry[1][col], m_entry[2][col] };
}

Matrix3& Matrix3::operator= (const Matrix4& mx)
{
    m_entry[0][0] = mx[0][0];
    m_entry[0][1] = mx[0][1];
    m_entry[0][2] = mx[0][2];
    m_entry[1][0] = mx[1][0];
    m_entry[1][1] = mx[1][1];
    m_entry[1][2] = mx[1][2];
    m_entry[2][0] = mx[2][0];
    m_entry[2][1] = mx[2][1];
    m_entry[2][2] = mx[2][2];
    return *this;
}

bool Matrix3::operator== (const Matrix3& mx) const
{
    return ((FloatCompare::isEqual(m_entry[0][0], mx.m_entry[0][0])) && (FloatCompare::isEqual(m_entry[0][1], mx.m_entry[0][1])) && (FloatCompare::isEqual(m_entry[0][2], mx.m_entry[0][2])) && (FloatCompare::isEqual(m_entry[1][0], mx.m_entry[1][0])) && (FloatCompare::isEqual(m_entry[1][1], mx.m_entry[1][1])) && (FloatCompare::isEqual(m_entry[1][2], mx.m_entry[1][2])) && (FloatCompare::isEqual(m_entry[2][0], mx.m_entry[2][0])) && (FloatCompare::isEqual(m_entry[2][1], mx.m_entry[2][1])) && (FloatCompare::isEqual(m_entry[2][2], mx.m_entry[2][2])));
}

bool Matrix3::operator!= (const Matrix3& mx) const
{
    return !(*this == mx);
}

Matrix3 Matrix3::operator+ (const Matrix3& mx) const
{
    return { m_entry[0][0] + mx.m_entry[0][0],
        m_entry[0][1] + mx.m_entry[0][1],
        m_entry[0][2] + mx.m_entry[0][2],
        m_entry[1][0] + mx.m_entry[1][0],
        m_entry[1][1] + mx.m_entry[1][1],
        m_entry[1][2] + mx.m_entry[1][2],
        m_entry[2][0] + mx.m_entry[2][0],
        m_entry[2][1] + mx.m_entry[2][1],
        m_entry[2][2] + mx.m_entry[2][2] };
}

Matrix3 Matrix3::operator- (const Matrix3& mx) const
{
    return { m_entry[0][0] - mx.m_entry[0][0],
        m_entry[0][1] - mx.m_entry[0][1],
        m_entry[0][2] - mx.m_entry[0][2],
        m_entry[1][0] - mx.m_entry[1][0],
        m_entry[1][1] - mx.m_entry[1][1],
        m_entry[1][2] - mx.m_entry[1][2],
        m_entry[2][0] - mx.m_entry[2][0],
        m_entry[2][1] - mx.m_entry[2][1],
        m_entry[2][2] - mx.m_entry[2][2] };
}

Matrix3 Matrix3::operator* (const Matrix3& mx) const
{
    return { m_entry[0][0] * mx.m_entry[0][0] + m_entry[0][1] * mx.m_entry[1][0] + m_entry[0][2] * mx.m_entry[2][0],
        m_entry[0][0] * mx.m_entry[0][1] + m_entry[0][1] * mx.m_entry[1][1] + m_entry[0][2] * mx.m_entry[2][1],
        m_entry[0][0] * mx.m_entry[0][2] + m_entry[0][1] * mx.m_entry[1][2] + m_entry[0][2] * mx.m_entry[2][2],
        m_entry[1][0] * mx.m_entry[0][0] + m_entry[1][1] * mx.m_entry[1][0] + m_entry[1][2] * mx.m_entry[2][0],
        m_entry[1][0] * mx.m_entry[0][1] + m_entry[1][1] * mx.m_entry[1][1] + m_entry[1][2] * mx.m_entry[2][1],
        m_entry[1][0] * mx.m_entry[0][2] + m_entry[1][1] * mx.m_entry[1][2] + m_entry[1][2] * mx.m_entry[2][2],
        m_entry[2][0] * mx.m_entry[0][0] + m_entry[2][1] * mx.m_entry[1][0] + m_entry[2][2] * mx.m_entry[2][0],
        m_entry[2][0] * mx.m_entry[0][1] + m_entry[2][1] * mx.m_entry[1][1] + m_entry[2][2] * mx.m_entry[2][1],
        m_entry[2][0] * mx.m_entry[0][2] + m_entry[2][1] * mx.m_entry[1][2] + m_entry[2][2] * mx.m_entry[2][2] };
}

Matrix3 Matrix3::operator* (float scalar) const
{
    return { m_entry[0][0] * scalar, m_entry[0][1] * scalar, m_entry[0][2] * scalar,
        m_entry[1][0] * scalar, m_entry[1][1] * scalar, m_entry[1][2] * scalar,
        m_entry[2][0] * scalar, m_entry[2][1] * scalar, m_entry[2][2] * scalar };
}

Matrix3 Matrix3::operator/ (float scalar) const
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    const float inv_scalar = 1.0f / scalar;
    return { m_entry[0][0] * inv_scalar, m_entry[0][1] * inv_scalar, m_entry[0][2] * inv_scalar,
        m_entry[1][0] * inv_scalar, m_entry[1][1] * inv_scalar, m_entry[1][2] * inv_scalar,
        m_entry[2][0] * inv_scalar, m_entry[2][1] * inv_scalar, m_entry[2][2] * inv_scalar };
}

Matrix3 Matrix3::operator- () const
{
    return { -m_entry[0][0], -m_entry[0][1], -m_entry[0][2], -m_entry[1][0], -m_entry[1][1], -m_entry[1][2], -m_entry[2][0], -m_entry[2][1], -m_entry[2][2] };
}

Matrix3& Matrix3::operator+= (const Matrix3& mx)
{
    m_entry[0][0] += mx.m_entry[0][0];
    m_entry[0][1] += mx.m_entry[0][1];
    m_entry[0][2] += mx.m_entry[0][2];
    m_entry[1][0] += mx.m_entry[1][0];
    m_entry[1][1] += mx.m_entry[1][1];
    m_entry[1][2] += mx.m_entry[1][2];
    m_entry[2][0] += mx.m_entry[2][0];
    m_entry[2][1] += mx.m_entry[2][1];
    m_entry[2][2] += mx.m_entry[2][2];
    return *this;
}

Matrix3& Matrix3::operator-= (const Matrix3& mx)
{
    m_entry[0][0] -= mx.m_entry[0][0];
    m_entry[0][1] -= mx.m_entry[0][1];
    m_entry[0][2] -= mx.m_entry[0][2];
    m_entry[1][0] -= mx.m_entry[1][0];
    m_entry[1][1] -= mx.m_entry[1][1];
    m_entry[1][2] -= mx.m_entry[1][2];
    m_entry[2][0] -= mx.m_entry[2][0];
    m_entry[2][1] -= mx.m_entry[2][1];
    m_entry[2][2] -= mx.m_entry[2][2];
    return *this;
}

Matrix3& Matrix3::operator*= (float scalar)
{
    m_entry[0][0] *= scalar;
    m_entry[0][1] *= scalar;
    m_entry[0][2] *= scalar;
    m_entry[1][0] *= scalar;
    m_entry[1][1] *= scalar;
    m_entry[1][2] *= scalar;
    m_entry[2][0] *= scalar;
    m_entry[2][1] *= scalar;
    m_entry[2][2] *= scalar;
    return *this;
}

Matrix3& Matrix3::operator/= (float scalar)
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    const float inv_scalar = 1.0f / scalar;
    m_entry[0][0] *= inv_scalar;
    m_entry[0][1] *= inv_scalar;
    m_entry[0][2] *= inv_scalar;
    m_entry[1][0] *= inv_scalar;
    m_entry[1][1] *= inv_scalar;
    m_entry[1][2] *= inv_scalar;
    m_entry[2][0] *= inv_scalar;
    m_entry[2][1] *= inv_scalar;
    m_entry[2][2] *= inv_scalar;
    return *this;
}

Vector3 Matrix3::operator* (const Vector3& vec) const
{
    return { m_entry[0][0] * vec.x() + m_entry[0][1] * vec.y() + m_entry[0][2] * vec.z(),
        m_entry[1][0] * vec.x() + m_entry[1][1] * vec.y() + m_entry[1][2] * vec.z(),
        m_entry[2][0] * vec.x() + m_entry[2][1] * vec.y() + m_entry[2][2] * vec.z() };
}

Matrix3 Matrix3::transpose() const
{
    return { m_entry[0][0], m_entry[1][0], m_entry[2][0], m_entry[0][1], m_entry[1][1], m_entry[2][1], m_entry[0][2], m_entry[1][2], m_entry[2][2] };
}

Matrix3 Matrix3::inverse() const
{
    Matrix3 inverse = adjoint();

    const float det = m_entry[0][0] * inverse.m_entry[0][0] + m_entry[0][1] * inverse.m_entry[1][0] + m_entry[0][2] * inverse.m_entry[2][0];

    assert(!FloatCompare::isEqual(det, 0.0f));

    inverse /= det;
    return inverse;
}

Matrix3 Matrix3::adjoint() const
{
    Matrix3 adjoint;
    adjoint.m_entry[0][0] = m_entry[1][1] * m_entry[2][2] - m_entry[1][2] * m_entry[2][1];
    adjoint.m_entry[0][1] = m_entry[0][2] * m_entry[2][1] - m_entry[0][1] * m_entry[2][2];
    adjoint.m_entry[0][2] = m_entry[0][1] * m_entry[1][2] - m_entry[0][2] * m_entry[1][1];
    adjoint.m_entry[1][0] = m_entry[1][2] * m_entry[2][0] - m_entry[1][0] * m_entry[2][2];
    adjoint.m_entry[1][1] = m_entry[0][0] * m_entry[2][2] - m_entry[0][2] * m_entry[2][0];
    adjoint.m_entry[1][2] = m_entry[0][2] * m_entry[1][0] - m_entry[0][0] * m_entry[1][2];
    adjoint.m_entry[2][0] = m_entry[1][0] * m_entry[2][1] - m_entry[1][1] * m_entry[2][0];
    adjoint.m_entry[2][1] = m_entry[0][1] * m_entry[2][0] - m_entry[0][0] * m_entry[2][1];
    adjoint.m_entry[2][2] = m_entry[0][0] * m_entry[1][1] - m_entry[0][1] * m_entry[1][0];
    return adjoint;
}

float Matrix3::determinant() const
{
    return m_entry[0][0] * (m_entry[1][1] * m_entry[2][2] - m_entry[1][2] * m_entry[2][1]) - m_entry[0][1] * (m_entry[1][0] * m_entry[2][2] - m_entry[1][2] * m_entry[2][0]) + m_entry[0][2] * (m_entry[1][0] * m_entry[2][1] - m_entry[1][1] * m_entry[2][0]);
}

std::tuple<Vector3, Radian> Matrix3::toAxisAngle() const
{
    // Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
    // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
    // I is the identity and
    //
    //       +-        -+
    //   P = |  0 -z +y |
    //       | +z  0 -x |
    //       | -y +x  0 |
    //       +-        -+
    //
    // If A > 0, R represents a counterclockwise rotation about the axis in
    // the sense of looking from the tip of the axis vector towards the
    // origin.  Some algebra will show that
    //
    //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
    //
    // In the event that A = pi, R-R^t = 0 which prevents us from extracting
    // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
    // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
    // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
    // it does not matter which sign you choose on the square roots.

    const float trace = m_entry[0][0] + m_entry[1][1] + m_entry[2][2];
    const float cos_value = 0.5f * (trace - 1.0f);
    const float angle = std::acos(cos_value); // in [0,PI]

    Vector3 axis;
    if (angle > 0.0f)
    {
        if (angle < Constants::PI)
        {
            axis[0] = m_entry[2][1] - m_entry[1][2];
            axis[1] = m_entry[0][2] - m_entry[2][0];
            axis[2] = m_entry[1][0] - m_entry[0][1];
            axis.normalizeSelf();
        }
        else
        {
            // angle is PI
            if (m_entry[0][0] >= m_entry[1][1])
            {
                // r00 >= r11
                if (m_entry[0][0] >= m_entry[2][2])
                {
                    // r00 is maximum diagonal term
                    axis[0] = 0.5f * sqrt(m_entry[0][0] - m_entry[1][1] - m_entry[2][2] + 1.0f);
                    const float half_inverse = 0.5f / axis[0];
                    axis[1] = half_inverse * m_entry[0][1];
                    axis[2] = half_inverse * m_entry[0][2];
                }
                else
                {
                    // r22 is maximum diagonal term
                    axis[2] = 0.5f * sqrt(m_entry[2][2] - m_entry[0][0] - m_entry[1][1] + 1.0f);
                    const float half_inverse = 0.5f / axis[2];
                    axis[0] = half_inverse * m_entry[0][2];
                    axis[1] = half_inverse * m_entry[1][2];
                }
            }
            else
            {
                // r11 > r00
                if (m_entry[1][1] >= m_entry[2][2])
                {
                    // r11 is maximum diagonal term
                    axis[1] = 0.5f * sqrt(m_entry[1][1] - m_entry[0][0] - m_entry[2][2] + 1.0f);
                    const float half_inverse = 0.5f / axis[1];
                    axis[0] = half_inverse * m_entry[0][1];
                    axis[2] = half_inverse * m_entry[1][2];
                }
                else
                {
                    // r22 is maximum diagonal term
                    axis[2] = 0.5f * sqrt(m_entry[2][2] - m_entry[0][0] - m_entry[1][1] + 1.0f);
                    const float half_inverse = 0.5f / axis[2];
                    axis[0] = half_inverse * m_entry[0][2];
                    axis[1] = half_inverse * m_entry[1][2];
                }
            }
        }
    }
    else
    {
        // The angle is 0 and the matrix is the identity.  Any axis will
        // work, so just use the x-axis.
        axis[0] = 1.0f;
        axis[1] = 0.0f;
        axis[2] = 0.0f;
    }
    return { axis, Radian(angle) };

}

Matrix3 Matrix3::fromEulerAnglesXyz(const EulerAngles& angles)
{
    return rotationX(angles.m_x) * (rotationY(angles.m_y) * rotationZ(angles.m_z));
}

Matrix3 Matrix3::fromEulerAnglesXzy(const EulerAngles& angles)
{
    return rotationX(angles.m_x) * (rotationZ(angles.m_z) * rotationY(angles.m_y));
}

Matrix3 Matrix3::fromEulerAnglesYxz(const EulerAngles& angles)
{
    return rotationY(angles.m_y) * (rotationX(angles.m_x) * rotationZ(angles.m_z));
}

Matrix3 Matrix3::fromEulerAnglesYzx(const EulerAngles& angles)
{
    return rotationY(angles.m_y) * (rotationZ(angles.m_z) * rotationX(angles.m_x));
}

Matrix3 Matrix3::fromEulerAnglesZxy(const EulerAngles& angles)
{
    return rotationZ(angles.m_z) * (rotationX(angles.m_x) * rotationY(angles.m_y));
}

Matrix3 Matrix3::fromEulerAnglesZyx(const EulerAngles& angles)
{
    return rotationZ(angles.m_z) * (rotationY(angles.m_y) * rotationX(angles.m_x));
}

EulerAngles Matrix3::toEulerAnglesXyz() const
{
    // rot =  cy*cz          -cy*sz           sy
    //        cz*sx*sy+cx*sz  cx*cz-sx*sy*sz -cy*sx
    //       -cx*cz*sy+sx*sz  cz*sx+cx*sy*sz  cx*cy
    if (m_entry[0][2] < 1.0f)
    {
        if (m_entry[0][2] > -1.0f)
        {
            const float x_angle = std::atan2(-m_entry[1][2], m_entry[2][2]);
            const float y_angle = std::asin(m_entry[0][2]);
            const float z_angle = std::atan2(-m_entry[0][1], m_entry[0][0]);
            return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
        }
        // WARNING.  Not unique.  XA - ZA = -atan2(r10,r11)
        const float x_angle = -atan2(m_entry[1][0], m_entry[1][1]);
        const float y_angle = -Constants::HALF_PI;
        return { Radian(x_angle), Radian(y_angle), Radian::ZERO };
    }
    // WARNING.  Not unique.  XAngle + ZAngle = atan2(r10,r11)
    const float x_angle = atan2(m_entry[1][0], m_entry[1][1]);
    const float y_angle = Constants::HALF_PI;
    return { Radian(x_angle), Radian(y_angle), Radian::ZERO };
}

EulerAngles Matrix3::toEulerAnglesXzy() const
{
    // rot =  cy*cz          -sz              cz*sy
    //        sx*sy+cx*cy*sz cx*cz          -cy*sx+cx*sy*sz
    //       -cx*sy+cy*sx*sz cz*sx           cx*cy+sx*sy*sz
    if (m_entry[0][1] < 1.0f)
    {
        if (m_entry[0][1] > -1.0f)
        {
            const float x_angle = std::atan2(m_entry[2][1], m_entry[1][1]);
            const float z_angle = std::asin(-m_entry[0][1]);
            const float y_angle = std::atan2(m_entry[0][2], m_entry[0][0]);
            return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
        }
        // WARNING.  Not unique.  XA - ZA = -atan2(r20,r22)
        const float x_angle = -std::atan2(m_entry[2][0], m_entry[2][2]);
        const float z_angle = Constants::HALF_PI;
        return { Radian(x_angle), Radian::ZERO, Radian(z_angle) };
    }
    // WARNING.  Not unique.  XA + ZA = atan2(r20,r22)
    const float x_angle = std::atan2(m_entry[2][0], m_entry[2][2]);
    const float z_angle = -Constants::HALF_PI;
    return { Radian(x_angle), Radian::ZERO, Radian(z_angle) };
}

EulerAngles Matrix3::toEulerAnglesYxz() const
{
    // rot =  cy*cz+sx*sy*sz  cz*sx*sy-cy*sz  cx*sy
    //        cx*sz           cx*cz          -sx
    //       -cz*sy+cy*sx*sz  cy*cz*sx+sy*sz  cx*cy
    if (m_entry[1][2] < 1.0f)
    {
        if (m_entry[1][2] > -1.0f)
        {
            const float y_angle = std::atan2(m_entry[0][2], m_entry[2][2]);
            const float x_angle = std::asin(-m_entry[1][2]);
            const float z_angle = std::atan2(m_entry[1][0], m_entry[1][1]);
            return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
        }
        // WARNING.  Not unique.  YA - ZA = atan2(r01,r00)
        const float y_angle = std::atan2(m_entry[0][1], m_entry[0][0]);
        const float x_angle = Constants::HALF_PI;
        return { Radian(x_angle), Radian(y_angle), Radian::ZERO };
    }
    // WARNING.  Not unique.  YA + ZA = atan2(-r01,r00)
    const float y_angle = std::atan2(-m_entry[0][1], m_entry[0][0]);
    const float x_angle = -Constants::HALF_PI;
    return { Radian(x_angle), Radian(y_angle), Radian::ZERO };
}

EulerAngles Matrix3::toEulerAnglesYzx() const
{
    // rot =  cy*cz           sx*sy-cx*cy*sz  cx*sy+cy*sx*sz
    //        sz              cx*cz          -cz*sx
    //       -cz*sy           cy*sx+cx*sy*sz  cx*cy-sx*sy*sz
    if (m_entry[1][0] < 1.0f)
    {
        if (m_entry[1][0] > -1.0f)
        {
            const float y_angle = std::atan2(-m_entry[2][0], m_entry[0][0]);
            const float z_angle = std::asin(m_entry[1][0]);
            const float x_angle = std::atan2(-m_entry[1][2], m_entry[1][1]);
            return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
        }
        // WARNING.  Not unique.  YA - XA = -atan2(r21,r22);
        const float y_angle = -std::atan2(m_entry[2][1], m_entry[2][2]);
        const float z_angle = -Constants::HALF_PI;
        return { Radian::ZERO, Radian(y_angle), Radian(z_angle) };
    }
    // WARNING.  Not unique.  YA + XA = atan2(r21,r22)
    const float y_angle = std::atan2(m_entry[2][1], m_entry[2][2]);
    const float z_angle = Constants::HALF_PI;
    return { Radian::ZERO, Radian(y_angle), Radian(z_angle) };
}

EulerAngles Matrix3::toEulerAnglesZxy() const
{
    // rot =  cy*cz-sx*sy*sz -cx*sz          cz*sy+cy*sx*sz
    //        cz*sx*sy+cy*sz  cx*cz          -cy*cz*sx+sy*sz
    //       -cx*sy           sx              cx*cy
    if (m_entry[2][1] < 1.0f)
    {
        if (m_entry[2][1] > -1.0f)
        {
            const float z_angle = std::atan2(-m_entry[0][1], m_entry[1][1]);
            const float x_angle = std::asin(m_entry[2][1]);
            const float y_angle = std::atan2(-m_entry[2][0], m_entry[2][2]);
            return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
        }
        // WARNING.  Not unique.  ZA - XA = -atan2(r12,r10)
        const float z_angle = -std::atan2(m_entry[0][2], m_entry[0][0]);
        const float x_angle = -Constants::HALF_PI;
        return { Radian(x_angle), Radian::ZERO, Radian(z_angle) };
    }
    // WARNING.  Not unique.  ZA + XA = atan2(r12,r10)
    const float z_angle = std::atan2(m_entry[0][2], m_entry[0][0]);
    const float x_angle = Constants::HALF_PI;
    return { Radian(x_angle), Radian::ZERO, Radian(z_angle) };
}

EulerAngles Matrix3::toEulerAnglesZyx() const
{
    // rot =  cy*cz           cz*sx*sy-cx*sz  cx*cz*sy+sx*sz
    //        cy*sz           cx*cz+sx*sy*sz -cz*sx+cx*sy*sz
    //       -sy              cy*sx           cx*cy
    if (m_entry[2][0] < 1.0f)
    {
        if (m_entry[2][0] > -1.0f)
        {
            const float z_angle = std::atan2(m_entry[1][0], m_entry[0][0]);
            const float y_angle = std::asin(-m_entry[2][0]);
            const float x_angle = std::atan2(m_entry[2][1], m_entry[2][2]);
            return { Radian(x_angle), Radian(y_angle), Radian(z_angle) };
        }
        // WARNING.  Not unique.  ZA - XA = -atan2(r01,r02)
        const float z_angle = -std::atan2(m_entry[0][1], m_entry[0][2]);
        const float y_angle = Constants::HALF_PI;
        return { Radian::ZERO, Radian(y_angle), Radian(z_angle) };
    }
    // WARNING.  Not unique.  ZA + XA = atan2(-r01,-r02)
    const float z_angle = std::atan2(-m_entry[0][1], -m_entry[0][2]);
    const float y_angle = -Constants::HALF_PI;
    return { Radian::ZERO, Radian(y_angle), Radian(z_angle) };
}

Matrix3 Matrix3::rotationX(const Radian& radian)
{
    const float cos_value = std::cos(radian.value());
    const float sin_value = std::sin(radian.value());
    return { 1.0f, 0.0f, 0.0f, 0.0f, cos_value, -sin_value, 0.0f, sin_value, cos_value };
}

Matrix3 Matrix3::rotationY(const Radian& radian)
{
    const float cos_value = std::cos(radian.value());
    const float sin_value = std::sin(radian.value());
    return { cos_value, 0.0f, sin_value, 0.0f, 1.0f, 0.0f, -sin_value, 0.0f, cos_value };
}

Matrix3 Matrix3::rotationZ(const Radian& radian)
{
    const float cos_value = std::cos(radian.value());
    const float sin_value = std::sin(radian.value());
    return { cos_value, -sin_value, 0.0f, sin_value, cos_value, 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix3 Matrix3::rotationYawPitchRoll(const Radian& yaw, const Radian& pitch, const Radian& roll)
{
    return rotationY(yaw) * rotationX(pitch) * rotationZ(roll);
}

Matrix3 Matrix3::sphericalLerp(float t, const Matrix3& rot0, const Matrix3& rot1)
{
    const Matrix3 prod = rot0.transposeTimes(rot1);
    auto [axis, angle] = prod.toAxisAngle();
    return rot0 * fromAxisAngle(axis, t * angle);
}

Matrix3 Matrix3::transposeTimes(const Matrix3& mx) const
{
    // A^T*B
    return { m_entry[0][0] * mx.m_entry[0][0] + m_entry[1][0] * mx.m_entry[1][0] + m_entry[2][0] * mx.m_entry[2][0],
        m_entry[0][0] * mx.m_entry[0][1] + m_entry[1][0] * mx.m_entry[1][1] + m_entry[2][0] * mx.m_entry[2][1],
        m_entry[0][0] * mx.m_entry[0][2] + m_entry[1][0] * mx.m_entry[1][2] + m_entry[2][0] * mx.m_entry[2][2],
        m_entry[0][1] * mx.m_entry[0][0] + m_entry[1][1] * mx.m_entry[1][0] + m_entry[2][1] * mx.m_entry[2][0],
        m_entry[0][1] * mx.m_entry[0][1] + m_entry[1][1] * mx.m_entry[1][1] + m_entry[2][1] * mx.m_entry[2][1],
        m_entry[0][1] * mx.m_entry[0][2] + m_entry[1][1] * mx.m_entry[1][2] + m_entry[2][1] * mx.m_entry[2][2],
        m_entry[0][2] * mx.m_entry[0][0] + m_entry[1][2] * mx.m_entry[1][0] + m_entry[2][2] * mx.m_entry[2][0],
        m_entry[0][2] * mx.m_entry[0][1] + m_entry[1][2] * mx.m_entry[1][1] + m_entry[2][2] * mx.m_entry[2][1],
        m_entry[0][2] * mx.m_entry[0][2] + m_entry[1][2] * mx.m_entry[1][2] + m_entry[2][2] * mx.m_entry[2][2] };
}

Matrix3 Matrix3::timesTranspose(const Matrix3& mx) const
{
    // A*B^T
    return { m_entry[0][0] * mx.m_entry[0][0] + m_entry[0][1] * mx.m_entry[0][1] + m_entry[0][2] * mx.m_entry[0][2],
        m_entry[0][0] * mx.m_entry[1][0] + m_entry[0][1] * mx.m_entry[1][1] + m_entry[0][2] * mx.m_entry[1][2],
        m_entry[0][0] * mx.m_entry[2][0] + m_entry[0][1] * mx.m_entry[2][1] + m_entry[0][2] * mx.m_entry[2][2],
        m_entry[1][0] * mx.m_entry[0][0] + m_entry[1][1] * mx.m_entry[0][1] + m_entry[1][2] * mx.m_entry[0][2],
        m_entry[1][0] * mx.m_entry[1][0] + m_entry[1][1] * mx.m_entry[1][1] + m_entry[1][2] * mx.m_entry[1][2],
        m_entry[1][0] * mx.m_entry[2][0] + m_entry[1][1] * mx.m_entry[2][1] + m_entry[1][2] * mx.m_entry[2][2],
        m_entry[2][0] * mx.m_entry[0][0] + m_entry[2][1] * mx.m_entry[0][1] + m_entry[2][2] * mx.m_entry[0][2],
        m_entry[2][0] * mx.m_entry[1][0] + m_entry[2][1] * mx.m_entry[1][1] + m_entry[2][2] * mx.m_entry[1][2],
        m_entry[2][0] * mx.m_entry[2][0] + m_entry[2][1] * mx.m_entry[2][1] + m_entry[2][2] * mx.m_entry[2][2] };
}


Vector2 Matrix3::transformCoordinate(const Vector2& v) const
{
    const float z = m_entry[2][0] * v.x() + m_entry[2][1] * v.y() + m_entry[2][2];
    assert(!FloatCompare::isEqual(z, 0.0f));
    const float inv_z = 1.0f / z;
    return { (m_entry[0][0] * v.x() + m_entry[0][1] * v.y() + m_entry[0][2]) * inv_z,
        (m_entry[1][0] * v.x() + m_entry[1][1] * v.y() + m_entry[1][2]) * inv_z };
}

Vector2 Matrix3::transform(const Vector2& v) const
{
    return { m_entry[0][0] * v.x() + m_entry[0][1] * v.y() + m_entry[0][2],
        m_entry[1][0] * v.x() + m_entry[1][1] * v.y() + m_entry[1][2] };
}

Vector2 Matrix3::transformVector(const Vector2& v) const
{
    return { m_entry[0][0] * v.x() + m_entry[0][1] * v.y(),
        m_entry[1][0] * v.x() + m_entry[1][1] * v.y() };
}

std::tuple<Vector2, float> Matrix3::transformVectorNormalized(const Vector2& v) const
{
    Vector2 result = { m_entry[0][0] * v.x() + m_entry[0][1] * v.y(),
        m_entry[1][0] * v.x() + m_entry[1][1] * v.y() };
    const float length = result.length();
    result.normalizeSelf();
    return { result, length };
}

float Matrix3::getMaxScale() const
{
    const auto v0 = Vector2(m_entry[0][0], m_entry[1][0]);
    const auto v1 = Vector2(m_entry[0][1], m_entry[1][1]);
    float max_s = v0.length();
    if (v1.length() > max_s) max_s = v1.length();
    return max_s;
}

const Matrix3 Math::Matrix3::ZERO = makeZero();
const Matrix3 Math::Matrix3::IDENTITY = makeIdentity();



namespace Math
{
    Matrix3 operator* (float scalar, const Matrix3& mx)
    {
        return mx * scalar;
    }
}
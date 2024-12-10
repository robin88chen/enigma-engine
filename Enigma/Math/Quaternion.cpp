#include "Quaternion.hpp"
#include "MathGlobal.hpp"
#include "Vector3.hpp"
#include "Matrix3.hpp"
#include "Radian.hpp"
#include <cassert>
#include <cmath>

using namespace Math;

Quaternion::Quaternion() : m_w(1.0f), m_x(0.0f), m_y(0.0f), m_z(0.0f)
{
}

Quaternion::Quaternion(float w, float x, float y, float z) : m_w(w), m_x(x), m_y(y), m_z(z)
{
}

Quaternion::operator const float* () const
{
    return &m_w;
}

Quaternion::operator float* ()
{
    return &m_w;
}

float Quaternion::w() const
{
    return m_w;
}

void Quaternion::w(float w)
{
    m_w = w;
}

float Quaternion::x() const
{
    return m_x;
}

void Quaternion::x(float x)
{
    m_x = x;
}

float Quaternion::y() const
{
    return m_y;
}

void Quaternion::y(float y)
{
    m_y = y;
}

float Quaternion::z() const
{
    return m_z;
}

void Quaternion::z(float z)
{
    m_z = z;
}

bool Quaternion::operator== (const Quaternion& quat) const
{
    return (FloatCompare::isEqual(m_w, quat.m_w) && FloatCompare::isEqual(m_x, quat.m_x)
        && FloatCompare::isEqual(m_y, quat.m_y) && FloatCompare::isEqual(m_z, quat.m_z));
}

bool Quaternion::operator!= (const Quaternion& quat) const
{
    return !(*this == quat);
}

Quaternion Quaternion::operator+ (const Quaternion& quat) const
{
    return { m_w + quat.m_w, m_x + quat.m_x, m_y + quat.m_y, m_z + quat.m_z };
}

Quaternion Quaternion::operator- (const Quaternion& quat) const
{
    return { m_w - quat.m_w, m_x - quat.m_x, m_y - quat.m_y, m_z - quat.m_z };
}

Quaternion Quaternion::operator* (const Quaternion& quat) const
{
    // NOTE:  Multiplication is not generally commutative, so in most
    // cases p*q != q*p.
    return { m_w * quat.m_w - m_x * quat.m_x - m_y * quat.m_y - m_z * quat.m_z,
             m_w * quat.m_x + m_x * quat.m_w + m_y * quat.m_z - m_z * quat.m_y,
             m_w * quat.m_y - m_x * quat.m_z + m_y * quat.m_w + m_z * quat.m_x,
             m_w * quat.m_z + m_x * quat.m_y - m_y * quat.m_x + m_z * quat.m_w };
}

Quaternion Quaternion::operator* (float scalar) const
{
    return { m_w * scalar, m_x * scalar, m_y * scalar, m_z * scalar };
}

Quaternion Quaternion::operator/ (float scalar) const
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    const float inv_scalar = 1.0f / scalar;
    return { m_w * inv_scalar, m_x * inv_scalar, m_y * inv_scalar, m_z * inv_scalar };
}

Quaternion Quaternion::operator- () const
{
    return { -m_w, -m_x, -m_y, -m_z };
}

Vector3 Quaternion::operator* (const Vector3& vec) const
{
    // nVidia SDK implementation
    const Vector3 qvec(m_x, m_y, m_z);
    Vector3 uv = qvec.cross(vec);
    Vector3 uuv = qvec.cross(uv);
    uv *= (2.0f * m_w);
    uuv *= 2.0f;
    return vec + uv + uuv;
}

Quaternion& Quaternion::operator+= (const Quaternion& quat)
{
    m_w += quat.m_w;
    m_x += quat.m_x;
    m_y += quat.m_y;
    m_z += quat.m_z;
    return *this;
}

Quaternion& Quaternion::operator-= (const Quaternion& quat)
{
    m_w -= quat.m_w;
    m_x -= quat.m_x;
    m_y -= quat.m_y;
    m_z -= quat.m_z;
    return *this;
}

Quaternion& Quaternion::operator*= (float scalar)
{
    m_w *= scalar;
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    return *this;
}

Quaternion& Quaternion::operator/= (float scalar)
{
    assert(!FloatCompare::isEqual(scalar, 0.0f));
    const float inv_scalar = 1.0f / scalar;
    m_w *= inv_scalar;
    m_x *= inv_scalar;
    m_y *= inv_scalar;
    m_z *= inv_scalar;
    return *this;
}

Quaternion Quaternion::fromRotationMatrix(const Matrix3& rot)
{
    // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
    // article "Quaternion Calculus and Fast Animation".
    const float trace = rot[0][0] + rot[1][1] + rot[2][2];
    float root;  // NOLINT(cppcoreguidelines-init-variables)
    if (trace > 0.0f)
    {
        // |w| > 1/2, may as well choose w > 1/2
        root = std::sqrt(trace + 1.0f);  // 2w
        const float w = 0.5f * root;
        root = 0.5f / root;  // 1/(4w)
        const float x = (rot[2][1] - rot[1][2]) * root;
        const float y = (rot[0][2] - rot[2][0]) * root;
        const float z = (rot[1][0] - rot[0][1]) * root;
        return { w, x, y, z };
    }
    // |w| <= 1/2
    constexpr std::array<int, 3> I_NEXT = { 1, 2, 0 };
    int i = 0;
    if (rot[1][1] > rot[0][0]) i = 1;
    if (rot[2][2] > rot[i][i]) i = 2;
    const int j = I_NEXT[i];
    const int k = I_NEXT[j];
    root = std::sqrt(rot[i][i] - rot[j][j] - rot[k][k] + 1.0f);
    std::array<float, 3> quat{};
    quat[i] = 0.5f * root;
    root = 0.5f / root;
    const float w = (rot[k][j] - rot[j][k]) * root;
    quat[j] = (rot[j][i] + rot[i][j]) * root;
    quat[k] = (rot[k][i] + rot[i][k]) * root;
    return { w, quat[0], quat[1], quat[2] };
}

Matrix3 Quaternion::toRotationMatrix() const
{
    const float two_x = 2.0f * m_x;
    const float two_y = 2.0f * m_y;
    const float two_z = 2.0f * m_z;
    const float two_xw = two_x * m_w;
    const float two_yw = two_y * m_w;
    const float two_zw = two_z * m_w;
    const float two_xx = two_x * m_x;
    const float two_xy = two_y * m_x;
    const float two_xz = two_z * m_x;
    const float two_yy = two_y * m_y;
    const float two_yz = two_z * m_y;
    const float two_zz = two_z * m_z;
    return { 1.0f - (two_yy + two_zz), two_xy - two_zw, two_xz + two_yw,
             two_xy + two_zw, 1.0f - (two_xx + two_zz), two_yz - two_xw,
             two_xz - two_yw, two_yz + two_xw, 1.0f - (two_xx + two_yy) };
}

Quaternion Quaternion::fromAxisAngle(const Vector3& axis, const Radian& angle)
{
    // assert:  axis[] is unit length
    //
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)
    assert(FloatCompare::isEqual(axis.squaredLength(), 1.0f));
    const float half_angle = 0.5f * angle.value();
    const float sin_half_angle = std::sin(half_angle);
    return { std::cos(half_angle), axis.x() * sin_half_angle, axis.y() * sin_half_angle, axis.z() * sin_half_angle };
}

std::tuple<Vector3, Radian> Quaternion::toAxisAngle() const
{
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)
    const float sqr_length = m_x * m_x + m_y * m_y + m_z * m_z;
    if (FloatCompare::isEqual(sqr_length, 0.0f)) return { Vector3::UNIT_X, Radian::ZERO };
    const float inv_length = 1.0f / std::sqrt(sqr_length);
    return { Vector3(m_x * inv_length, m_y * inv_length, m_z * inv_length), Radian(2.0f * std::acos(m_w)) };
}

float Quaternion::length() const
{
    return std::sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
}

float Quaternion::squaredLength() const
{
    return m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z;
}

float Quaternion::dot(const Quaternion& quat) const
{
    return m_w * quat.m_w + m_x * quat.m_x + m_y * quat.m_y + m_z * quat.m_z;
}

Quaternion Quaternion::exp() const
{
    // If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
    // use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.
    const float angle = std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    const float sin_angle = std::sin(angle);
    if (std::abs(sin_angle) > FloatCompare::zeroTolerance())
    {
        const float multiplier = sin_angle / angle;
        return { std::cos(angle), m_x * multiplier, m_y * multiplier, m_z * multiplier };
    }
    return { std::cos(angle), m_x, m_y, m_z };
}

Quaternion Quaternion::normalize() const
{
    const float len = length();
    assert(!FloatCompare::isEqual(len, 0.0f));
    const float inv_len = 1.0f / len;
    return { m_w * inv_len, m_x * inv_len, m_y * inv_len, m_z * inv_len };
}

Quaternion Quaternion::inverse() const
{
    const float sqr_length = m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z;
    assert(!FloatCompare::isEqual(sqr_length, 0.0f));
    const float inv_sqr_length = 1.0f / sqr_length;
    return { m_w * inv_sqr_length, -m_x * inv_sqr_length, -m_y * inv_sqr_length, -m_z * inv_sqr_length };
}

Quaternion Quaternion::conjugate() const
{
    return { m_w, -m_x, -m_y, -m_z };
}

Quaternion Quaternion::log() const
{
    // If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) = sin(A)*(x*i+y*j+z*k)
    // since sin(A)/A has limit 1.
    const float angle = std::acos(m_w);
    const float sin_angle = std::sin(angle);
    const float multiplier = (std::abs(sin_angle) > FloatCompare::zeroTolerance()) ? angle / sin_angle : 1.0f;
    return { 0.0f, m_x * multiplier, m_y * multiplier, m_z * multiplier };
}

Vector3 Quaternion::rotate(const Vector3& vec) const
{
    // Given a vector u = (x0,y0,z0) and a unit length quaternion
    // q = <w,x,y,z>, the vector v = (x1,y1,z1) which represents the
    // rotation of u by q is v = q*u*q^{-1} where * indicates quaternion
    // multiplication and where u is treated as the quaternion <0,x0,y0,z0>.
    // Note that q^{-1} = <w,-x,-y,-z>, so no real work is required to
    // invert q.  Now
    //
    //   q*u*q^{-1} = q*<0,x0,y0,z0>*q^{-1}
    //     = q*(x0*i+y0*j+z0*k)*q^{-1}
    //     = x0*(q*i*q^{-1})+y0*(q*j*q^{-1})+z0*(q*k*q^{-1})
    //
    // As 3-vectors, q*i*q^{-1}, q*j*q^{-1}, and 2*k*q^{-1} are the columns
    // of the rotation matrix computed in Quaternion<float>::ToRotationMatrix.
    // The vector v is obtained as the product of that rotation matrix with
    // vector u.  As such, the quaternion representation of a rotation
    // matrix requires less space than the matrix and more time to compute
    // the rotated vector.  Typical space-time tradeoff...

    const Matrix3 rot = toRotationMatrix();
    return rot * vec;
}

Quaternion Quaternion::sphericalLerp(float t, const Quaternion& p, const Quaternion& q, bool shortest_path)
{
    const float cs = p.dot(q);

    if (const float angle = std::acos(cs); std::fabs(angle) >= FloatCompare::zeroTolerance())
    {
        const float sn = std::sin(angle);
        const float inv_sn = 1.0f / sn;
        float coeff0 = std::sin((1.0f - t) * angle) * inv_sn;
        const float coeff1 = std::sin(t * angle) * inv_sn;
        // Do we need to invert rotation?
        if (cs < 0.0f && shortest_path)
        {
            coeff0 = -coeff0;
        }

        // taking the complement requires renormalisation
        const Quaternion r(coeff0 * p + coeff1 * q);
        return r.normalize();
        //}
        //else
        //{
        //*this = coeff0 * p + coeff1 * q;
        //}
    }
    return p;
}

Quaternion Quaternion::sphericalLerpExtraSpins(float t, const Quaternion& p, const Quaternion& q, int extra_spins)
{
    const float cs = p.dot(q);

    if (const float angle = std::acos(cs); std::fabs(angle) >= FloatCompare::zeroTolerance())
    {
        const float sn = std::sin(angle);
        const float phase = Constants::PI * static_cast<float>(extra_spins) * t;
        const float inv_sn = 1.0f / sn;
        const float coeff0 = std::sin((1.0f - t) * angle - phase) * inv_sn;
        const float coeff1 = std::sin(t * angle + phase) * inv_sn;
        return coeff0 * p + coeff1 * q;
    }
    return p;
}

Quaternion Quaternion::intermediate(const Quaternion& q0, const Quaternion& q1, const Quaternion& q2)
{
    constexpr float MINUS_QUATER = -0.25f;
    // assert:  Q0, Q1, Q2 all unit-length
    assert(FloatCompare::isEqual(q0.squaredLength() * q1.squaredLength() * q2.squaredLength(), 1.0f));
    const Quaternion q1_con = q1.conjugate();
    const Quaternion p0 = q1_con * q0;
    const Quaternion p2 = q1_con * q2;
    const Quaternion arg = p0.log() + p2.log();
    return q1 * (arg * MINUS_QUATER).exp();
}

Quaternion Quaternion::sphericalQuadInterpolation(float t, const Quaternion& q0, const Quaternion& a0, const Quaternion& a1, const Quaternion& q1, bool shortest_path)
{
    const float slerp_t = 2.0f * t * (1.0f - t);
    const Quaternion slerp_p = sphericalLerp(t, q0, q1, shortest_path);
    const Quaternion slerp_q = sphericalLerp(t, a0, a1, false);
    return sphericalLerp(slerp_t, slerp_p, slerp_q, false);
}

const Quaternion Quaternion::IDENTITY{ 1.0f, 0.0f, 0.0f, 0.0f };
const Quaternion Quaternion::ZERO{ 0.0f, 0.0f, 0.0f, 0.0f };

namespace Math
{
    Quaternion operator* (float scalar, const Quaternion& quat)
    {
        return quat * scalar;
    }
}


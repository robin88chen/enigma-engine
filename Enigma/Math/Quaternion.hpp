/*********************************************************************
 * \file   Quaternion.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef QUATERNION_HPP
#define QUATERNION_HPP
#include <tuple>
namespace Math
{
    class Matrix3;
    class Vector3;
    class Radian;
    /** Math Lib Quaternion
    @remarks
    A quaternion is q = w + x*i + y*j + z*k where (w,x,y,z) is not
     necessarily a unit length vector in 4D. */
    class Quaternion
    {
    public:
        // construction
        Quaternion();  ///< w=x=y=z=0.0
        Quaternion(float w, float x, float y, float z);

        explicit operator const float* () const;
        explicit operator float* ();
        [[nodiscard]] float w() const;
        void w(float w);
        [[nodiscard]] float x() const;
        void x(float x);
        [[nodiscard]] float y() const;
        void y(float y);
        [[nodiscard]] float z() const;
        void z(float z);

        bool operator== (const Quaternion& quat) const; ///< 浮點數值比較
        bool operator!= (const Quaternion& quat) const; ///< 浮點數值比較

        Quaternion operator+ (const Quaternion& quat) const;
        Quaternion operator- (const Quaternion& quat) const;
        Quaternion operator* (const Quaternion& quat) const;
        Quaternion operator* (float scalar) const;
        Quaternion operator/ (float scalar) const;
        Quaternion operator- () const;
        Vector3 operator* (const Vector3& vec) const;

        Quaternion& operator+= (const Quaternion& quat);
        Quaternion& operator-= (const Quaternion& quat);
        Quaternion& operator*= (float scalar);
        Quaternion& operator/= (float scalar);

        static Quaternion fromRotationMatrix(const Matrix3& rot);
        [[nodiscard]] Matrix3 toRotationMatrix() const;
        /** @remarks
         assert:  axis[] is unit length \n
         The quaternion representing the rotation is \n
           q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)  */
        static Quaternion fromAxisAngle(const Vector3& axis, const Radian& angle);
        [[nodiscard]] std::tuple<Vector3, Radian> toAxisAngle() const;

        [[nodiscard]] float length() const;  ///< length of 4-tuple
        [[nodiscard]] float squaredLength() const;  ///< squared length of 4-tuple
        [[nodiscard]] float dot(const Quaternion& quat) const;  ///< dot product of 4-tuples
        [[nodiscard]] Quaternion normalize() const;  ///< make the 4-tuple unit length
        [[nodiscard]] Quaternion inverse() const;  ///< apply to non-zero quaternion
        [[nodiscard]] Quaternion conjugate() const;
        [[nodiscard]] Quaternion exp() const;  ///< apply to quaternion with w = 0
        [[nodiscard]] Quaternion log() const;  ///< apply to unit-length quaternion

        /** rotation of a vector by a quaternion */
        [[nodiscard]] Vector3 rotate(const Vector3& vec) const;

        /// spherical linear interpolation, t=0 --> P, t=1 --> Q
        static Quaternion sphericalLerp(float t, const Quaternion& p, const Quaternion& q, bool shortest_path = false);

        /// spherical linear interpolation, t=0 --> P, t=1 --> Q
        static Quaternion sphericalLerpExtraSpins(float t, const Quaternion& p, const Quaternion& q, int extra_spins);

        /// intermediate terms for spherical quadratic interpolation
        static Quaternion intermediate(const Quaternion& q0, const Quaternion& q1, const Quaternion& q2);

        /// spherical quadratic interpolation
        static Quaternion sphericalQuadInterpolation(float t, const Quaternion& q0, const Quaternion& a0, const Quaternion& a1, const Quaternion& q1, bool shortest_path = false);

        static const Quaternion IDENTITY;  // the identity rotation
        static const Quaternion ZERO;

    private:
        float m_w, m_x, m_y, m_z;
    };
    Quaternion operator* (float scalar, const Quaternion& quat);
}

#endif // QUATERNION_HPP

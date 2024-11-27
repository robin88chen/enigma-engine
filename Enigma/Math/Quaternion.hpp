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
    struct QuaternionDecompose;
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

        /// quaternion for the input rotation matrix
        Quaternion(const Matrix3& rot);

        /// quaternion for the rotation of the axis-angle pair
        Quaternion(const Vector3& axis, float angle);

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
        static Quaternion sphericalLerp(float t, const Quaternion& p, const Quaternion& q, bool shortestPath = false);

        /// spherical linear interpolation, t=0 --> P, t=1 --> Q
        static Quaternion sphericalLerpExtraSpins(float t, const Quaternion& p, const Quaternion& q, int extraSpins);

        /// intermediate terms for spherical quadratic interpolation
        static Quaternion intermediate(const Quaternion& q0, const Quaternion& q1, const Quaternion& q2);

        /// spherical quadratic interpolation
        static Quaternion sphericalQuadInterpolation(float t, const Quaternion& q0, const Quaternion& a0, const Quaternion& a1, const Quaternion& q1, bool shortestPath = false);

        /** Compute a quaternion that rotates unit-length vector V1 to unit-length
         vector V2.  The rotation is about the axis perpendicular to both V1 and
         V2, with angle of that between V1 and V2.  If V1 and V2 are parallel,
         any axis of rotation will do, such as the permutation (z2,x2,y2), where
         V2 = (x2,y2,z2). */
        static Quaternion align(const Vector3& vec1, const Vector3& vec2);

        /** Decompose a quaternion into q = q_twist * q_swing, where q is 'this'
         quaternion.  If V1 is the input axis and V2 is the rotation of V1 by
         q, q_swing represents the rotation about the axis perpendicular to
         V1 and V2 (see Quaternion::Align), and q_twist is a rotation about V1. */
        QuaternionDecompose decomposeTwistTimesSwing(const Vector3& vec1) const;

        /** Decompose a quaternion into q = q_swing * q_twist, where q is 'this'
         quaternion.  If V1 is the input axis and V2 is the rotation of V1 by
         q, q_swing represents the rotation about the axis perpendicular to
         V1 and V2 (see Quaternion::Align), and q_twist is a rotation about V1. */
        QuaternionDecompose decomposeSwingTimesTwist(const Vector3& vec1) const;
        //@}

        /** @name special values */
        //@{
        static const Quaternion IDENTITY;  // the identity rotation
        static const Quaternion ZERO;
        //@}

    private:

        void implicitFromRotationMatrix(const Matrix3& rot);
        void implicitFromAxisAngle(const Vector3& axis, float angle);
        float m_w, m_x, m_y, m_z;
    };

    struct QuaternionDecompose
    {
        Quaternion m_swing;
        Quaternion m_twist;
    };

    Quaternion operator* (float scalar, const Quaternion& quat);
}

#endif // QUATERNION_HPP

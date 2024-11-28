/*********************************************************************
 * \file   Matrix3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef MATRIX3_HPP
#define MATRIX3_HPP
#include <array>
#include <tuple>
namespace Math
{
    class Vector2;
    class Vector3;
    class Matrix4;
    class Radian;
    struct EulerAngles;
    /** Math Lib Matrix3
    @remarks
     Matrix operations are applied on the left.  For example, given a matrix M
     and a vector V, matrix-times-vector is M*V.  That is, V is treated as a
     column vector.  Similarly, to apply two matrix operations M0
     and M1, in that order, you compute M1*M0 so that the transform of a vector
     is (M1*M0)*V = M1*(M0*V).
    @par
    The layout of the matrix entries is shown below:
    <pre>
    [ m[0][0]  m[0][1] m[0][2] ]
    [ m[1][0]  m[1][1] m[1][2] ]
    [ m[2][0]  m[2][1] m[2][2] ]
    </pre>
    @par
    Rotation matrices are of the form
    <pre>
       RX =    1       0       0
               0     cos(t) -sin(t)
               0     sin(t)  cos(t)
     where t > 0 indicates a clockwise rotation in the yz-plane
       RY =  cos(t)    0     sin(t)
               0       1       0
            -sin(t)    0     cos(t)
     where t > 0 indicates a clockwise rotation in the zx-plane
       RZ =  cos(t) -sin(t)    0
             sin(t)  cos(t)    0
               0       0       1
     where t > 0 indicates a clockwise rotation in the xy-plane.
    </pre>
    */
    class Matrix3
    {
    public:
        /// zero matrix
        Matrix3();
        /// input Mrc is in row r, column c.
        Matrix3(float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22);
        /** Create a matrix from an array of numbers.  The input array is \n
        entry[0..8]={m00,m01,m02,m10,m11,m12,m20,m21,m22} */
        explicit Matrix3(const std::array<float, 9>& m);
        /** Create from Matrix 4x4 */
        explicit Matrix3(const Matrix4& m);

        static Matrix3 makeZero();
        static Matrix3 makeIdentity();
        static Matrix3 makeDiagonal(float m00, float m11, float m22);
        static Matrix3 fromAxisAngle(const Vector3& axis, const Radian& angle);
        /** vectors are rows of the matrix (use for space transform) */
        static Matrix3 fromRowVectors(const std::array<Vector3, 3>& rows);
        /** vectors are columns of the matrix (use for pivot rotation) */
        static Matrix3 fromColumnVectors(const std::array<Vector3, 3>& columns);

        explicit operator const float* () const;
        explicit operator float* ();
        const float* operator[] (unsigned row) const;
        float* operator[] (unsigned row);
        float operator() (unsigned row, unsigned col) const;
        void setRow(unsigned row, const Vector3& v);
        [[nodiscard]] Vector3 getRow(unsigned row) const;
        void setColumn(unsigned col, const Vector3& v);
        [[nodiscard]] Vector3 getColumn(unsigned col) const;

        Matrix3& operator= (const Matrix4& mx);  ///< 左上角的 3x3 matrix

        bool operator== (const Matrix3& mx) const;  ///< 浮點數值比較
        bool operator!= (const Matrix3& mx) const;  ///< 浮點數值比較

        Matrix3 operator+ (const Matrix3& mx) const;
        Matrix3 operator- (const Matrix3& mx) const;
        Matrix3 operator* (const Matrix3& mx) const;
        Matrix3 operator* (float scalar) const;
        Matrix3 operator/ (float scalar) const;
        Matrix3 operator- () const;

        Matrix3& operator+= (const Matrix3& mx);
        Matrix3& operator-= (const Matrix3& mx);
        Matrix3& operator*= (float scalar);
        Matrix3& operator/= (float scalar);

        Vector3 operator* (const Vector3& v) const;  //< M * v

        [[nodiscard]] Matrix3 transpose() const;  // M^T
        [[nodiscard]] Matrix3 inverse() const;
        [[nodiscard]] Matrix3 adjoint() const;
        [[nodiscard]] float determinant() const;
        [[nodiscard]] std::tuple<Vector3, Radian> toAxisAngle() const;

        static Matrix3 rotationX(const Radian& radian);
        static Matrix3 rotationY(const Radian& radian);
        static Matrix3 rotationZ(const Radian& radian);
        /** 先對Z軸轉(roll),再對X軸轉(pitch),最後對Y軸轉(yaw) */
        static Matrix3 rotationYawPitchRoll(const Radian& yaw, const Radian& pitch, const Radian& roll);

        /** Spherical Lerp (spherical linear interpolation) without quaternions.
            @remark Computes R(t) = R0*(Transpose(R0)*R1)^t.  If Q is a rotation matrix with
         unit-length axis U and angle A, then Q^t is a rotation matrix with
         unit-length axis U and rotation angle t*A. */
        static Matrix3 sphericalLerp(float t, const Matrix3& rot0, const Matrix3& rot1);

        /** TransposeTimes M^T * mx */
        [[nodiscard]] Matrix3 transposeTimes(const Matrix3& mx) const;
        /** TimesTranspose M * mx^T */
        [[nodiscard]] Matrix3 timesTranspose(const Matrix3& mx) const;


        /** transforms the vector, pV (x, y, 1), by the matrix, projecting the result back into z=1 */
        [[nodiscard]] Vector2 transformCoordinate(const Vector2& v) const;
        /** transforms the vector, pV (x, y, 1), by the matrix */
        [[nodiscard]] Vector2 transform(const Vector2& v) const;
        /** transforms the vector  (x, y, 0) of the vector, pV, by the matrix */
        [[nodiscard]] Vector2 transformVector(const Vector2& v) const;
        /** transforms the vector  (x, y, 0) of the vector, pV, by the matrix, and normalize result, return length if needed */
        [[nodiscard]] std::tuple<Vector2, float> transformVectorNormalized(const Vector2& v) const;

        [[nodiscard]] float getMaxScale() const;

        static const Matrix3 ZERO;
        static const Matrix3 IDENTITY;

    private:
        float m_entry[3][3];
    };

    Matrix3 operator* (float scalar, const Matrix3& mx);
}

#endif // MATRIX3_HPP

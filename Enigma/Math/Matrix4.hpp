/*********************************************************************
 * \file   Matrix4.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef MATRIX4_HPP
#define MATRIX4_HPP
#include <array>
#include <tuple>
namespace Math
{
    class Quaternion;
    class Matrix3;
    class Vector3;
    class Vector4;
    class Radian;
    /** Math Lib Matrix4
    @remarks
    Matrix operations are applied on the left.  For example, given a matrix M
    and a vector V, matrix-times-vector is M*V.  That is, V is treated as a
    column vector.  Similarly, to apply two matrix operations M0
    and M1, in that order, you compute M1*M0 so that the transform of a vector
    is (M1*M0)*V = M1*(M0*V).
    @par
    The generic form M * V which shows the layout of the matrix
    entries is shown below:
    <pre>
    [ m[0][0]  m[0][1]  m[0][2]  m[0][3] ]   {x}
    | m[1][0]  m[1][1]  m[1][2]  m[1][3] | * {y}
    | m[2][0]  m[2][1]  m[2][2]  m[2][3] |   {z}
    [ m[3][0]  m[3][1]  m[3][2]  m[3][3] ]   {1}
    </pre>
    @par
    旋轉與縮放的3x3矩陣在4x4矩陣的左上部份，translate是4x4矩陣的最右邊column.
    */
    class Matrix4
    {
    public:
        /// zero matrix.
        Matrix4();
        /// input Mrc is in row r, column c.
        Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);
        /** Create a matrix from an array of numbers.  The input array is \n
        entry[0..15]={m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,m23,m30,m31,m32,m33} */
        explicit Matrix4(const std::array<float, 16>& m);
        /** Create from Matrix 3x3 */
        explicit Matrix4(const Matrix3& mx);
        /** Create from Matrix 3x3 and translate column */
        explicit Matrix4(const Matrix3& rotation_matrix, const Vector3& position);

        [[nodiscard]] static Matrix4 makeZero();
        [[nodiscard]] static Matrix4 makeIdentity();

        explicit operator const float* () const;
        explicit operator float* ();
        const float* operator[] (unsigned row) const;
        float* operator[] (unsigned row);
        float operator() (unsigned row, unsigned col) const;
        void setRow(unsigned row, const Vector4& vec);
        [[nodiscard]] Vector4 getRow(unsigned row) const;
        void setColumn(unsigned col, const Vector4& vec);
        [[nodiscard]] Vector4 getColumn(unsigned col) const;

        Matrix4& operator= (const Matrix3& mx);  ///< right column & bottom row will be 0, and m33 is 1

        bool operator== (const Matrix4& mx) const; ///< 浮點數值比較
        bool operator!= (const Matrix4& mx) const; ///< 浮點數值比較

        Matrix4 operator+ (const Matrix4& mx) const;
        Matrix4 operator- (const Matrix4& mx) const;
        Matrix4 operator* (const Matrix4& mx) const;
        Matrix4 operator* (float scalar) const;
        Matrix4 operator/ (float scalar) const;
        Matrix4 operator- () const;

        Matrix4& operator+= (const Matrix4& mx);
        Matrix4& operator-= (const Matrix4& mx);
        Matrix4& operator*= (float scalar);
        Matrix4& operator/= (float scalar);

        /** 沒有做homogenize, i.e. w未必等於1.0 */
        Vector4 operator* (const Vector4& vec) const;  //< M * v
        /** 傳回homogenize後的vector3, ADR : 這容易誤解，又與底下的 transform 重複, 移除之 */
        //Vector3 operator* (const Vector3& vec) const;

        [[nodiscard]] Matrix4 transpose() const;  // M^T
        [[nodiscard]] Matrix4 inverse() const;
        [[nodiscard]] Matrix4 adjoint() const;
        [[nodiscard]] float determinant() const;

        static const Matrix4 ZERO;
        static const Matrix4 IDENTITY;

        /** transforms the vector, pV (x, y, z, 1), by the matrix, projecting the result back into w=1 */
        [[nodiscard]] Vector3 transformCoordinate(const Vector3& vec) const;
        /** transforms the vector, pV (x, y, z, 1), by the matrix */
        [[nodiscard]] Vector3 transform(const Vector3& vec) const;
        /** transforms the vector  (x, y, z, 0) of the vector, pV, by the matrix */
        [[nodiscard]] Vector3 transformVector(const Vector3& vec) const;

        [[nodiscard]] static Matrix4 makeTranslateTransform(float tx, float ty, float tz);
        [[nodiscard]] static Matrix4 makeTranslateTransform(const Vector3& vec);
        [[nodiscard]] static Matrix4 makeScaleTransform(float sx, float sy, float sz);
        [[nodiscard]] static Matrix4 makeScaleTransform(const Vector3& vec);
        /** radian > 0 indicates a clockwise rotation in the yz-plane */
        [[nodiscard]] static Matrix4 makeRotationXTransform(const Radian& radian);
        /** radian > 0 indicates a clockwise rotation in the xz-plane */
        [[nodiscard]] static Matrix4 makeRotationYTransform(const Radian& radian);
        /** radian > 0 indicates a clockwise rotation in the xy-plane */
        [[nodiscard]] static Matrix4 makeRotationZTransform(const Radian& radian);
        /** 先對Z軸轉(roll),再對X軸轉(pitch),最後對Y軸轉(yaw) */
        [[nodiscard]] static Matrix4 makeRotationYawPitchRoll(const Radian& yaw, const Radian& pitch, const Radian& roll);
        /** matrix from SRT
        @remark
        <pre>
        [ Sx*R[0][0]  Sy*R[0][1]  Sz*R[0][2]  Tx ]
        | Sx*R[1][0]  Sy*R[1][1]  Sz*R[1][2]  Ty |
        | Sx*R[2][0]  Sy*R[2][1]  Sz*R[2][2]  Tz |
        [      0           0           0       1 ]
        R is Rotate Matrix from Quaternion
        </pre>
        */
        [[nodiscard]] static Matrix4 fromScaleRotationTranslate(const Vector3& scale, const Matrix3& rot, const Vector3& trans);
        [[nodiscard]] static Matrix4 fromScaleQuaternionTranslate(const Vector3& scale, const Quaternion& rot, const Vector3& trans);

        /** 最右邊的column */
        [[nodiscard]] Vector3 extractTranslation() const;
        /** 假設並沒有shear scale */
        [[nodiscard]] Vector3 extractScale() const;
        /** 去掉translate & scale取出的rotation (no shear scale) */
        [[nodiscard]] Matrix3 extractRotation() const;
        /** 分解SRT */
        [[nodiscard]] std::tuple<Vector3, Quaternion, Vector3> unmatrixScaleQuaternionTranslation() const;
        [[nodiscard]] std::tuple<Vector3, Matrix3, Vector3> unmatrixScaleRotateMatrixTranslation() const;

        [[nodiscard]] float getMaxScale() const;

    private:
        // minor matrix determinant
        [[nodiscard]] float minorDeterminant(const int r0, const int r1, const int r2, const int c0, const int c1, const int c2) const;

        float m_entry[4][4];
    };

    /** scalar * Matrix */
    Matrix4 operator* (float scalar, const Matrix4& mx);
}

#endif // MATRIX4_HPP

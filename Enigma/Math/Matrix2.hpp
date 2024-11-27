/*********************************************************************
 * \file   Matrix2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef MATRIX2_HPP
#define MATRIX2_HPP
#include <array>

namespace Math
{
    class Vector2;
    class Radian;

    /** Math Lib Matrix2
      @remarks
          The layout of the matrix entries is shown below:
      <pre>
      [ m[0][0]  m[0][1] ]
      [ m[1][0]  m[1][1] ]
      </pre>
      @par
        Rotation matrices are of the form
          <pre>
         R = cos(t) -sin(t)
             sin(t)  cos(t)
        </pre>
        where t > 0 indicates a clockwise (bcz. left-hand coordinate) rotation in the xy-plane.
    */
    class Matrix2
    {
    public:
        /// zero matrix.
        Matrix2();
        /// input Mrc is in row r, column c.
        Matrix2(float m00, float m01, float m10, float m11);
        /** Create a matrix from an array of numbers.  The input array is \n
           entry[0..3] = {m00,m01,m10,m11} */
        explicit Matrix2(const std::array<float, 4>& m);

        static Matrix2 makeZero();
        static Matrix2 makeIdentity();
        static Matrix2 makeDiagonal(float m00, float m11);
        static Matrix2 fromAngle(const Radian& angle);

        explicit operator const float* () const;
        explicit operator float* ();
        const float* operator[] (unsigned row) const;
        float* operator[] (unsigned row);
        float operator() (unsigned row, unsigned col) const;
        void setRow(unsigned row, const Vector2& v);
        [[nodiscard]] Vector2 getRow(int row) const;
        void setColumn(int col, const Vector2& v);
        [[nodiscard]] Vector2 getColumn(int col) const;

        bool operator== (const Matrix2& mx) const;  ///< 浮點數值比較
        bool operator!= (const Matrix2& mx) const;  ///< 浮點數值比較

        Matrix2 operator+ (const Matrix2& mx) const;
        Matrix2 operator- (const Matrix2& mx) const;
        Matrix2 operator* (const Matrix2& mx) const;
        Matrix2 operator* (float scalar) const;
        Matrix2 operator/ (float scalar) const;
        Matrix2 operator- () const;

        Matrix2& operator+= (const Matrix2& mx);
        Matrix2& operator-= (const Matrix2& mx);
        Matrix2& operator*= (float scalar);
        Matrix2& operator/= (float scalar);

        Vector2 operator* (const Vector2& v) const;  //< M * v

        [[nodiscard]] Matrix2 transpose() const;  // M^T
        [[nodiscard]] Matrix2 inverse() const;
        [[nodiscard]] Matrix2 adjoint() const;
        [[nodiscard]] float determinant() const;
        /** @remark The matrix must be a rotation for these functions to be valid. */
        [[nodiscard]] Radian rotationAngle() const;

        static const Matrix2 ZERO;
        static const Matrix2 IDENTITY;

    private:
        float m_entry[2][2];
    };

    Matrix2 operator* (float scalar, const Matrix2& mx);
}

#endif // MATRIX2_HPP

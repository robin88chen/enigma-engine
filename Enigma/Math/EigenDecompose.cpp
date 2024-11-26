#include "EigenDecompose.hpp"
#include "MathGlobal.hpp"
#include "Matrix2.hpp"
#include "Matrix3.hpp"
#include <cassert>
#include <cmath>

namespace Math
{
    // Support for eigen decomposition.  The Tri-diagonalize function applies
    // a Householder transformation to the matrix.  If that transformation
    // is the identity (the matrix is already tri-diagonal), then the return
    // value is 'false'.  Otherwise, the transformation is a reflection and
    // the return value is 'true'.  The QLAlgorithm returns 'true' iff the
    // QL iteration scheme converged.
    [[nodiscard]] static std::tuple<Matrix3, std::array<float, 3>, std::array<float, 2>, bool> triDiagonalize(const Matrix3& matrix);
    [[nodiscard]] static std::tuple<Matrix3, std::array<float, 3>, std::array<float, 2>, bool> qlAlgorithm(const Matrix3& matrix, const std::array<float, 3>& in_diagonal, const std::array<float, 2>& in_sub_diagonal);
    EigenDecompose<Matrix2> eigenDecomposition(const Matrix2& matrix)
    {
        Matrix2 rot;
        const float trace = matrix[0][0] + matrix[1][1];
        const float diff = matrix[0][0] - matrix[1][1];
        const float discr = sqrt(diff * diff + 4.0f * matrix[0][1] * matrix[0][1]);
        const float eig_val0 = 0.5f * (trace - discr);
        const float eig_val1 = 0.5f * (trace + discr);
        const Matrix2 diag = Matrix2::makeDiagonal(eig_val0, eig_val1);

        float cos_value; // NOLINT(cppcoreguidelines-init-variables)
        float sin_value; // NOLINT(cppcoreguidelines-init-variables)
        if (diff >= 0.0f)
        {
            cos_value = matrix[0][1];
            sin_value = eig_val0 - matrix[0][0];
        }
        else
        {
            cos_value = eig_val0 - matrix[1][1];
            sin_value = matrix[0][1];
        }
        const float tmp = std::sqrt(cos_value * cos_value + sin_value * sin_value);
        cos_value /= tmp;
        sin_value /= tmp;

        rot[0][0] = cos_value;
        rot[0][1] = -sin_value;
        rot[1][0] = sin_value;
        rot[1][1] = cos_value;

        return { rot, diag };
    }

    EigenDecompose<Matrix3> eigenDecomposition(const Matrix3& matrix)
    {
        // Factor M = R*D*R^T.  The columns of R are the eigenvectors.  The
        // diagonal entries of D are the corresponding eigenvalues.
        auto [diag_mx, diagonal_diag, sub_diagonal_diag, is_reflection] = triDiagonalize(matrix);
        auto [rotmx, diagonal, sub_diagonal, is_converged] = qlAlgorithm(diag_mx, diagonal_diag, sub_diagonal_diag);
        assert(is_converged);

        // (insertion) sort eigenvalues in increasing order, d0 <= d1 <= d2

        if (diagonal[1] < diagonal[0])
        {
            // swap d0 and d1
            float save_value = diagonal[0];
            diagonal[0] = diagonal[1];
            diagonal[1] = save_value;

            // swap V0 and V1
            for (int i = 0; i < 3; i++)
            {
                save_value = rotmx[i][0];
                rotmx[i][0] = rotmx[i][1];
                rotmx[i][1] = save_value;
            }
            is_reflection = !is_reflection;
        }

        if (diagonal[2] < diagonal[1])
        {
            // swap d1 and d2
            float save_value = diagonal[1];
            diagonal[1] = diagonal[2];
            diagonal[2] = save_value;

            // swap V1 and V2
            for (int i = 0; i < 3; i++)
            {
                save_value = rotmx[i][1];
                rotmx[i][1] = rotmx[i][2];
                rotmx[i][2] = save_value;
            }
            is_reflection = !is_reflection;
        }

        if (diagonal[1] < diagonal[0])
        {
            // swap d0 and d1
            float save_value = diagonal[0];
            diagonal[0] = diagonal[1];
            diagonal[1] = save_value;

            // swap V0 and V1
            for (int i = 0; i < 3; i++)
            {
                save_value = rotmx[i][0];
                rotmx[i][0] = rotmx[i][1];
                rotmx[i][1] = save_value;
            }
            is_reflection = !is_reflection;
        }

        const Matrix3 diagmx = Matrix3::makeDiagonal(diagonal[0], diagonal[1], diagonal[2]);

        if (is_reflection)
        {
            // The orthogonal transformation that diagonalizes M is a reflection.
            // Make the eigenvectors a right--handed system by changing sign on
            // the last column.
            rotmx[0][2] = -rotmx[0][2];
            rotmx[1][2] = -rotmx[1][2];
            rotmx[2][2] = -rotmx[2][2];
        }
        return { rotmx, diagmx };

    }

    std::tuple<Matrix3, std::array<float, 3>, std::array<float, 2>, bool> triDiagonalize(const Matrix3& matrix)
    {
        // Householder reduction T = Q^t M Q
        //   Input:
        //     mat, symmetric 3x3 matrix M
        //   Output:
        //     mat, orthogonal matrix Q (a reflection)
        //     diag, diagonal entries of T
        //     subd, subdiagonal entries of T (T is symmetric)
        std::array<float, 3> diagonal{};
        std::array<float, 2> sub_diagonal{};
        Matrix3 q;
        const float m00 = matrix[0][0];
        float m01 = matrix[0][1];
        float m02 = matrix[0][2];
        const float m11 = matrix[1][1];
        const float m12 = matrix[1][2];
        const float m22 = matrix[2][2];

        diagonal[0] = m00;
        if (std::fabs(m02) >= FloatCompare::ZERO_TOLERANCE)
        {
            sub_diagonal[0] = std::sqrt(m01 * m01 + m02 * m02);
            const float inv_length = 1.0f / sub_diagonal[0];
            m01 *= inv_length;
            m02 *= inv_length;
            const float tmp = 2.0f * m01 * m12 + m02 * (m22 - m11);
            diagonal[1] = m11 + m02 * tmp;
            diagonal[2] = m22 - m02 * tmp;
            sub_diagonal[1] = m12 - m01 * tmp;

            q = Matrix3(1.0f, 0.0f, 0.0f, 0.0f, m01, m02, 0.0f, m02, -m01);
            return { q, diagonal, sub_diagonal, true };
        }
        diagonal[1] = m11;
        diagonal[2] = m22;
        sub_diagonal[0] = m01;
        sub_diagonal[1] = m12;
        q = Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        return { q, diagonal, sub_diagonal, false };
    }
    // NOLINTBEGIN(readability-function-cognitive-complexity)
    std::tuple<Matrix3, std::array<float, 3>, std::array<float, 2>, bool> qlAlgorithm(const Matrix3& matrix, const std::array<float, 3>& in_diagonal, const std::array<float, 2>& in_sub_diagonal)
    {
        // This is an implementation of the symmetric QR algorithm from the book
        // "Matrix Computations" by Gene H. Golub and Charles F. Van Loan, second
        // edition.  The algorithm is 8.2.3.  The implementation has a slight
        // variation to actually make it a QL algorithm, and it traps the case
        // when either of the subdiagonal terms s0 or s1 is zero and reduces the
        // 2-by-2 subblock directly.
        Matrix3 m = matrix;
        std::array<float, 3> diagonal = in_diagonal;
        std::array<float, 2> subdiagonal = in_sub_diagonal;
        constexpr int MAX_ITERATION = 32;
        for (int i = 0; i < MAX_ITERATION; i++)
        {
            float sum = std::fabs(diagonal[0]) + std::fabs(diagonal[1]);
            if (FloatCompare::isEqual(std::fabs(subdiagonal[0]) + sum, sum))
            {
                // The matrix is effectively
                //       +-        -+
                //   M = | d0  0  0 |
                //       | 0  d1 s1 |
                //       | 0  s1 d2 |
                //       +-        -+

                // Test whether M is diagonal (within numerical round-off).
                sum = std::fabs(diagonal[1]) + std::fabs(diagonal[2]);
                if (FloatCompare::isEqual(std::fabs(subdiagonal[1]) + sum, sum))
                {
                    return { m, diagonal, subdiagonal, true };
                }

                // Compute the eigenvalues as roots of a quadratic equation.
                sum = diagonal[1] + diagonal[2];
                const float diff = diagonal[1] - diagonal[2];
                const float discr = std::sqrt(diff * diff + 4.0f * subdiagonal[1] * subdiagonal[1]);
                const float eig_value0 = 0.5f * (sum - discr);
                const float eig_value1 = 0.5f * (sum + discr);

                float cos_value; // NOLINT(cppcoreguidelines-init-variables)
                float sin_value; // NOLINT(cppcoreguidelines-init-variables)
                // Compute the Givens rotation.
                if (diff >= 0.0f)
                {
                    cos_value = subdiagonal[1];
                    sin_value = diagonal[1] - eig_value0;
                }
                else
                {
                    cos_value = diagonal[2] - eig_value0;
                    sin_value = subdiagonal[1];
                }
                float tmp = 1.0f / std::sqrt(cos_value * cos_value + sin_value * sin_value);
                cos_value *= tmp;
                sin_value *= tmp;

                // Postmultiply the current orthogonal matrix with the Givens
                // rotation.
                for (int row_index = 0; row_index < 3; row_index++)
                {
                    tmp = matrix[row_index][2];
                    m[row_index][2] = sin_value * matrix[row_index][1] + cos_value * tmp;
                    m[row_index][1] = cos_value * matrix[row_index][1] - sin_value * tmp;
                }

                // Update the tridiagonal matrix.
                diagonal[1] = eig_value0;
                diagonal[2] = eig_value1;
                subdiagonal[0] = 0.0f;
                subdiagonal[1] = 0.0f;
                return { m, diagonal, subdiagonal, true };
            }

            sum = std::fabs(diagonal[1]) + std::fabs(diagonal[2]);
            if (FloatCompare::isEqual(std::fabs(subdiagonal[1]) + sum, sum))
            {
                // The matrix is effectively
                //       +-         -+
                //   M = | d0  s0  0 |
                //       | s0  d1  0 |
                //       | 0   0  d2 |
                //       +-         -+

                // Test whether M is diagonal (within numerical round-off).
                sum = std::fabs(diagonal[0]) + std::fabs(diagonal[1]);
                if (FloatCompare::isEqual(std::fabs(subdiagonal[0]) + sum, sum))
                {
                    return { m, diagonal, subdiagonal, true };
                }

                // Compute the eigenvalues as roots of a quadratic equation.
                sum = diagonal[0] + diagonal[1];
                const float diff = diagonal[0] - diagonal[1];
                const float discr = std::sqrt(diff * diff + 4.0f * subdiagonal[0] * subdiagonal[0]);
                const float eig_value0 = 0.5f * (sum - discr);
                const float eig_value1 = 0.5f * (sum + discr);

                float cos_value; // NOLINT(cppcoreguidelines-init-variables)
                float sin_value; // NOLINT(cppcoreguidelines-init-variables)
                // Compute the Givens rotation.
                if (diff >= 0.0f)
                {
                    cos_value = subdiagonal[0];
                    sin_value = diagonal[0] - eig_value0;
                }
                else
                {
                    cos_value = diagonal[1] - eig_value0;
                    sin_value = subdiagonal[0];
                }
                float tmp = 1.0f / std::sqrt(cos_value * cos_value + sin_value * sin_value);
                cos_value *= tmp;
                sin_value *= tmp;

                // Postmultiply the current orthogonal matrix with the Givens
                // rotation.
                for (int row_index = 0; row_index < 3; row_index++)
                {
                    tmp = matrix[row_index][1];
                    m[row_index][1] = sin_value * matrix[row_index][0] + cos_value * tmp;
                    m[row_index][0] = cos_value * matrix[row_index][0] - sin_value * tmp;
                }

                // Update the tridiagonal matrix.
                diagonal[0] = eig_value0;
                diagonal[1] = eig_value1;
                subdiagonal[0] = 0.0f;
                subdiagonal[1] = 0.0f;
                return { m, diagonal, subdiagonal, true };
            }

            // The matrix is
            //       +-        -+
            //   M = | d0 s0  0 |
            //       | s0 d1 s1 |
            //       | 0  s1 d2 |
            //       +-        -+

            // Set up the parameters for the first pass of the QL step.  The
            // value for A is the difference between diagonal term D[2] and the
            // implicit shift suggested by Wilkinson.
            float ratio = (diagonal[1] - diagonal[0]) / (2.0f * subdiagonal[0]);
            float root = std::sqrt(1.0f + ratio * ratio);
            float b_value = subdiagonal[1];
            float a_value = diagonal[2] - diagonal[0];
            if (ratio >= 0.0f)
            {
                a_value += subdiagonal[0] / (ratio + root);
            }
            else
            {
                a_value += subdiagonal[0] / (ratio - root);
            }

            float cos_value; // NOLINT(cppcoreguidelines-init-variables)
            float sin_value; // NOLINT(cppcoreguidelines-init-variables)
            // Compute the Givens rotation for the first pass.
            if (std::fabs(b_value) >= std::fabs(a_value))
            {
                ratio = a_value / b_value;
                sin_value = 1.0f / std::sqrt(1.0f + ratio * ratio);
                cos_value = ratio * sin_value;
            }
            else
            {
                ratio = b_value / a_value;
                cos_value = 1.0f / std::sqrt(1.0f + ratio * ratio);
                sin_value = ratio * cos_value;
            }

            // Postmultiply the current orthogonal matrix with the Givens
            // rotation.
            for (int row_index = 0; row_index < 3; row_index++)
            {
                const float tmp = matrix[row_index][2];
                m[row_index][2] = sin_value * matrix[row_index][1] + cos_value * tmp;
                m[row_index][1] = cos_value * matrix[row_index][1] - sin_value * tmp;
            }

            // Set up the parameters for the second pass of the QL step.  The
            // values tmp0 and tmp1 are required to fully update the tridiagonal
            // matrix at the end of the second pass.
            float tmp0 = (diagonal[1] - diagonal[2]) * sin_value +
                2.0f * subdiagonal[1] * cos_value;
            const float tmp1 = cos_value * subdiagonal[0];
            b_value = sin_value * subdiagonal[0];
            a_value = cos_value * tmp0 - subdiagonal[1];
            tmp0 *= sin_value;

            // Compute the Givens rotation for the second pass.  The subdiagonal
            // term S[1] in the tridiagonal matrix is updated at this time.
            if (std::fabs(b_value) >= std::fabs(a_value))
            {
                ratio = a_value / b_value;
                root = std::sqrt(1.0f + ratio * ratio);
                subdiagonal[1] = b_value * root;
                sin_value = 1.0f / root;
                cos_value = ratio * sin_value;
            }
            else
            {
                ratio = b_value / a_value;
                root = std::sqrt(1.0f + ratio * ratio);
                subdiagonal[1] = a_value * root;
                cos_value = 1.0f / root;
                sin_value = ratio * cos_value;
            }

            // Postmultiply the current orthogonal matrix with the Givens
            // rotation.
            for (int row_index = 0; row_index < 3; row_index++)
            {
                const float tmp = matrix[row_index][1];
                m[row_index][1] = sin_value * matrix[row_index][0] + cos_value * tmp;
                m[row_index][0] = cos_value * matrix[row_index][0] - sin_value * tmp;
            }

            // Complete the update of the tridiagonal matrix.
            const float tmp2 = diagonal[1] - tmp0;
            diagonal[2] += tmp0;
            tmp0 = (diagonal[0] - tmp2) * sin_value + 2.0f * tmp1 * cos_value;
            subdiagonal[0] = cos_value * tmp0 - tmp1;
            tmp0 *= sin_value;
            diagonal[1] = tmp2 + tmp0;
            diagonal[0] -= tmp0;
        }
        return { m, diagonal, subdiagonal, false };
    }
    // NOLINTEND(readability-function-cognitive-complexity)
}
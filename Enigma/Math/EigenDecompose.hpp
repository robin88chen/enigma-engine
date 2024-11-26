/*********************************************************************
 * \file   EigenDecompose.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef EIGEN_DECOMPOSE_HPP
#define EIGEN_DECOMPOSE_HPP

namespace Math
{
    class Matrix2;
    class Matrix3;
    template<class T> struct EigenDecompose
    {
        T m_rot;
        T m_diag;
    };
    /** Eigen Decomposition
    @remark  The matrix must be symmetric.  Factor M = R * D * R^T where \n
     R = [u0|u1] is a rotation matrix with columns u0 and u1 and \n
     D = diag(d0,d1) is a diagonal matrix whose diagonal entries are d0 and
     d1. \n The eigenvector u[i] corresponds to eigenvector d[i].  The
     eigenvalues are ordered as d0 <= d1. */
    [[nodiscard]] EigenDecompose<Matrix2> eigenDecomposition(const Matrix2& matrix);

    /** Eigen Decomposition
    @remark  The matrix must be symmetric.  Factor M = R * D * R^T where \n
    R = [u0|u1|u2] is a rotation matrix with columns u0, u1 and u2 and \n
    D = diagonal(d0,d1,d2) is a diagonal matrix whose diagonal entries are d0, d1 and
    d2. \n The eigenvector u[i] corresponds to eigenvector d[i].  The
    eigenvalues are ordered as d0 <= d1 <= d2. */
    [[nodiscard]] EigenDecompose<Matrix3> eigenDecomposition(const Matrix3& matrix);
}

#endif // EIGEN_DECOMPOSE_HPP

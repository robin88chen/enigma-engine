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
    template<class T> struct EigenDecompose
    {
        T m_rot;
        T m_diag;
    };
}

#endif // EIGEN_DECOMPOSE_HPP

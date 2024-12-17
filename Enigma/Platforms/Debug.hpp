/*****************************************************************
 * \file   Debug.hpp
 * \brief  將這個header視為在Core Layer, 而實作視為在Infrastructure Layer
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 ******************************************************************/
#ifndef PLATFORMS_DEBUG_HPP
#define PLATFORMS_DEBUG_HPP

namespace Platforms
{
    class Debug
    {
    public:
        static int printf(const char* format, ...);
        static int errorPrintf(const char* format, ...);
    };
}

#endif // PLATFORMS_DEBUG_HPP

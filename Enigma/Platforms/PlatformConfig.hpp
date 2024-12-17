/*****************************************************************
 * \file   PlatformConfig.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 ******************************************************************/
#ifndef PLATFORM_CONFIG_HPP
#define PLATFORM_CONFIG_HPP

 // define supported target platform.
#define PLATFORM_UNKNOWN            0
#define PLATFORM_WIN32              1
#define PLATFORM_ANDROID            2
#define PLATFORM_IOS                3
#define PLATFORM_MAC                4

// Determine target platform by compile environment macro.
#define TARGET_PLATFORM             PLATFORM_UNKNOWN

// win32
#if defined(WIN32)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_WIN32
#endif

// android
#if defined(ANDROID)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_ANDROID
#endif

#endif // PLATFORM_CONFIG_HPP

/*!
 * Copyright (c) 2016-2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef CAL_CONFIG_H
#define CAL_CONFIG_H

#if defined(_MSC_VER)
    #define CAL_EXPORT         __declspec(dllexport)
    #define CAL_IMPORT         __declspec(dllimport)
    #define CAL_INLINE         __inline
    #define CAL_FORCEINLINE    __forceinline
    #define CAL_DEPRECATED     __declspec(deprecated)
    #define CAL_ALIGNED(x)     __declspec(align(x))
    #define CAL_UNUSED(x)      x
#elif defined(__MINGW32__)
    #define CAL_EXPORT         __declspec(dllexport)
    #define CAL_IMPORT         __declspec(dllimport)
    #define CAL_INLINE         inline
    #define CAL_FORCEINLINE    inline
    #define CAL_DEPRECATED     __declspec(deprecated)
    #define CAL_ALIGNED(x)     __declspec(align(x))
    #define CAL_UNUSED(x)      x __attribute__((unused))
#elif defined(__GNUG__) && __GNUG__ >= 4 || defined(__clang__)
    #define CAL_EXPORT         __attribute__((visibility("default")))
    #define CAL_IMPORT         __attribute__((visibility("default")))
    #define CAL_INLINE         inline
    #define CAL_FORCEINLINE    inline __attribute__((always_inline))
    #define CAL_DEPRECATED     __attribute__((deprecated))
    #define CAL_ALIGNED(x)     __attribute__((aligned(x)))
    #define CAL_UNUSED(x)      x __attribute__((unused))
#else
    #define CAL_EXPORT
    #define CAL_IMPORT
    #define CAL_INLINE         inline
    #define CAL_FORCEINLINE    inline
    #define CAL_DEPRECATED
    #define CAL_ALIGNED(x)
    #define CAL_UNUSED(x)      x
#endif

#ifdef CAL_DLL_EXPORTS
    #define CAL_API CAL_EXPORT
#else
    #define CAL_API CAL_IMPORT
#endif

#if defined(__MINGW32__)
    #define CAL_PLATFORM_MINGW
#elif (defined(linux) || defined(__linux) || defined(__linux__) || defined(__GLIBC__)) && !defined(_CRAYC) && !defined(__FreeBSD_kernel__) && !defined(__GNU__)
    #define CAL_PLATFORM_LINUX
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    #define CAL_PLATFORM_WIN32
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
    #define CAL_PLATFORM_MACOS
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__FreeBSD_kernel__)
    #define CAL_PLATFORM_BSD
#endif

#endif /* CAL_CONFIG_H */

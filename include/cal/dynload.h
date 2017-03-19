/*!
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_DYNLOAD_H
#define CAL_DYNLOAD_H

#include <cal/config.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#    include <windows.h>
#else
#    include <dlfcn.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

CAL_INLINE void* cal_loadlibrary(
    const char* filepath,
    int flags
) {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return LoadLibraryEx(filepath, NULL, flags);
#else
    return dlopen(filepath, flags);
#endif
}

CAL_INLINE int cal_freelibrary(
    void* library_handle
) {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return FreeLibrary(library_handle);
#else
    return dlclose(library_handle);
#endif
}

#ifdef __cplusplus
}
#endif

#endif

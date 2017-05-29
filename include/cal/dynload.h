/*!
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_DYNLOAD_H
#define CAL_DYNLOAD_H

#include <cal/config.h>

// TODO: common flags
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#    include <windows.h>
#else
#    include <dlfcn.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

static CAL_FORCEINLINE void* cal_loadlibrary(
    const char* filepath,
    int flags
) {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return LoadLibraryEx(filepath, NULL, flags);
#else
    return dlopen(filepath, flags);
#endif
}

static CAL_FORCEINLINE void* cal_getsymbol(
    void* library_handle,
    const char* symbol_name
) {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return GetProcAddress(library_handle, symbol_name);
#else
    return dlsym(library_handle, symbol_name);
#endif
}

static CAL_FORCEINLINE int cal_freelibrary(
    void* library_handle
) {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return (FreeLibrary(library_handle) != 0) ? 0 : 1;
#else
    return dlclose(library_handle);
#endif
}

#ifdef __cplusplus
}
#endif

#endif

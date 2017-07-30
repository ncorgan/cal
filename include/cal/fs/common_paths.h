/*!
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_FS_COMMON_PATHS_H
#define CAL_FS_COMMON_PATHS_H

#include <cal/config.h>

#include <stdlib.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#    define CAL_FS_COMMON_PATHS_SEPARATOR "\\"
#else
#    define CAL_FS_COMMON_PATHS_SEPARATOR "/"
#endif

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#include <windows.h>
#elif defined(CAL_PLATFORM_LINUX)
#include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

static CAL_FORCEINLINE const char* cal_appdata_dir()
{
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return getenv("APPDATA");
#else
    return getenv("HOME");
#endif
}

static CAL_FORCEINLINE ssize_t cal_current_exe(
    char* buffer,
    size_t buffer_len
)
{
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return (ssize_t)GetModuleFileName(NULL, buffer, (DWORD)buffer_len);
#elif defined(CAL_PLATFORM_LINUX)
    return readlink("/proc/self/exe", buffer, buffer_len);
#else
    // TODO: OS X
    return 0;
#endif
}

static const char* cal_tmp_dir()
{
    const char* ret = getenv("TMP");
    if(ret) {
        return ret;
    }

    ret = getenv("TMPDIR");
    if(ret) {
        return ret;
    }

    ret = getenv("TEMP");
    if(ret) {
        return ret;
    }

    // Windows should always have one of the above set.
    return "/tmp";
}

#ifdef __cplusplus
}
#endif

#endif

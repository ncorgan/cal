/*!
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_PLATFORM_HOSTINFO_H
#define CAL_PLATFORM_HOSTINFO_H

#include <cal/config.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#    include <windows.h>
#else
#    include <unistd.h>
#endif


#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)

long cal_gethostid();

#else

static CAL_FORCEINLINE long cal_gethostid()
{
    return gethostid();
}

#endif

static CAL_INLINE int cal_gethostname(
    char* buffer,
    size_t buffer_len
)
{
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    DWORD internal_buffer_len = (DWORD)buffer_len;
    return GetComputerName(buffer, &internal_buffer_len) ? 0 : 1;
#else
    return gethostname(buffer, buffer_len);
#endif
}

static CAL_INLINE long cal_getpagesize()
{
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    SYSTEM_INFO system_info;
    GetNativeSystemInfo(&system_info);
    return (long)system_info.dwPageSize;
#else
    return (long)getpagesize();
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* CAL_PLATFORM_HOSTINFO_H */

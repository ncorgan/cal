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

static long cal_gethostid()
{
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    // Hopefully it's a safe assumption that a Windows machine has a C:\ drive.
    char szVolName[MAX_PATH+1], szFileSysName[MAX_PATH+1];
    DWORD dwSerialNumber, dwMaxComponentLen, dwFileSysFlags;
    GetVolumeInformation("C:\\", szVolName, MAX_PATH,
        &dwSerialNumber, &dwMaxComponentLen,
        &dwFileSysFlags, szFileSysName, sizeof(szFileSysName));

    return (long)dwSerialNumber;
#else
    return gethostid();
#endif
}

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

#ifdef __cplusplus
}
#endif

#endif /* CAL_PLATFORM_HOSTINFO_H */

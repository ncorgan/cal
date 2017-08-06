/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <cal/text.h>
#include <cal/platform/hostinfo.h>

#include <stdint.h>
#include <string.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)

long cal_gethostid()
{
    char szVolName[MAX_PATH+1], szFileSysName[MAX_PATH+1];
    DWORD dwSerialNumber, dwMaxComponentLen, dwFileSysFlags;
    GetVolumeInformation("C:\\", szVolName, MAX_PATH,
        &dwSerialNumber, &dwMaxComponentLen,
        &dwFileSysFlags, szFileSysName, sizeof(szFileSysName));

    if(dwSerialNumber == 0)
    {
        // Typically, it's safe to use the C:\ drive, but if not, fall back
        // to the root of the current directory. This is less deterministic,
        // but it's something.
        GetVolumeInformation(NULL, szVolName, MAX_PATH,
            &dwSerialNumber, &dwMaxComponentLen,
            &dwFileSysFlags, szFileSysName, sizeof(szFileSysName));
    }

    return (long)dwSerialNumber;
}

#endif
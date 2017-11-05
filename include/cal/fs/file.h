/*!
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_FS_FILE_H
#define CAL_FS_FILE_H

#include <cal/config.h>

#include <stdbool.h>
#include <stdlib.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#include <windows.h>
#elif defined(CAL_PLATFORM_LINUX)
#include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

static CAL_INLINE bool cal_does_file_exist(
    const char* filepath
)
{
    if(!filepath)
    {
        return false;
    }

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return PathFileExists(filepath);
#else
    return (access(filepath, F_OK) != -1);
#endif
}

static CAL_INLINE size_t cal_get_filesize(
    const char* filepath
)
{
    if(!filepath)
    {
        return 0;
    }

    FILE* f = fopen(filepath, "rb");
    if(!f)
    {
        return 0;
    }

    fseek(f, 0, SEEK_END);
    size_t ret = ftell(f);
    fclose(f);

    return ret;
}

#ifdef __cplusplus
}
#endif

#endif

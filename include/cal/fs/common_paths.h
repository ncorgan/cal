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

#ifdef __cplusplus
extern "C" {
#endif

static CAL_FORCEINLINE const char* cal_appdata_dir() {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return getenv("APPDATA");
#else
    return getenv("HOME");
#endif
}

static const char* cal_tmp_dir() {
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

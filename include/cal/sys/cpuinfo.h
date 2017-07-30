/*!
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_SYS_CPUINFO_H
#define CAL_SYS_CPUINFO_H

#include <cal/config.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#    include <windows.h>
#else
#    include <unistd.h>
#endif

static CAL_FORCEINLINE long cal_cpu_count() {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return 0;
#else
    // TODO: does this work with OS X?
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

#ifdef __cplusplus
}
#endif

#endif

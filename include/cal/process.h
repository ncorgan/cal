/*!
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_PROCESS_H
#define CAL_PROCESS_H

#include <cal/config.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#    include <windows.h>
#else
#    include <sys/syscall.h>
#    include <sys/types.h>
#    include <unistd.h>
#endif

static CAL_INLINE int cal_getpid() {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return GetCurrentProcessId();
#else
    return getpid();
#endif
}

static CAL_INLINE int cal_gettid() {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return GetCurrentThreadId();
#elif defined(CAL_PLATFORM_MACOS)
    return syscall(SYS_thread_selfid);
#elif defined(CAL_PLATFORM_BSD)
    long ret;
    syscall(SYS_thr_self, &ret);
    return (int)ret;
#else
    return syscall(SYS_gettid);
#endif
}

#ifdef __cplusplus
}
#endif

#endif

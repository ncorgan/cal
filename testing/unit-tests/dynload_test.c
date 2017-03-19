/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/dynload.h>

static void dynload_test() {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    const char* libname = "dynlib.dll";
    int flags = 0;
#else
    const char* libname = "libdynlib.so";
    int flags = RTLD_LAZY;
#endif

    void* library_handle = cal_loadlibrary(libname, flags);
    TEST_ASSERT_NOT_NULL(library_handle);

    int result = cal_freelibrary(library_handle);
    TEST_ASSERT_EQUAL(0, result);
}

CAL_TEST_MAIN(
    CAL_TEST(dynload_test)
)

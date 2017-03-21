/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/fs.h>

#include <stdio.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#include <shlwapi.h>
#endif

// TODO: replace with CAL version when implemented
static int file_exists(
    const char* filepath
) {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return PathFileExists(filepath) ? 1 : 0;
#else
    FILE* file = fopen(filepath, "rb");
    if(file) {
        fclose(file);
        return 1;
    } else {
        return 0;
    }
#endif
}

static void appdata_dir_test() {
    const char* appdata_dir = cal_appdata_dir();
    TEST_ASSERT_NOT_NULL(appdata_dir);
    TEST_ASSERT_TRUE(file_exists(appdata_dir));
}

static void tmp_dir_test() {
    const char* tmp_dir = cal_tmp_dir();
    TEST_ASSERT_NOT_NULL(tmp_dir);
    TEST_ASSERT_TRUE(file_exists(tmp_dir));
}

CAL_TEST_MAIN(
    CAL_TEST(appdata_dir_test)
    CAL_TEST(tmp_dir_test)
)

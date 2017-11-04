/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

// Must be set before anything else to work
#if defined(_MSC_VER)
#    define _CRT_SECURE_NO_WARNINGS
#endif

#include "cal_test.h"

#include <cal/fs/common_paths.h>

#include <stdio.h>

#include <string.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#include <shlwapi.h>
#endif

#define CAL_BUFFER_LEN 1024

// TODO: replace with CAL version when implemented
static int file_exists(
    const char* filepath
)
{
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return PathFileExists(filepath) ? 1 : 0;
#else
    FILE* file = fopen(filepath, "rb");
    if(file)
    {
        fclose(file);
        return 1;
    }
    else
    {
        return 0;
    }
#endif
}

static void appdata_dir_test() {
    const char* appdata_dir = cal_appdata_dir();
    TEST_ASSERT_NOT_NULL(appdata_dir);
    TEST_ASSERT_TRUE(file_exists(appdata_dir));
}

static void current_exe_test()
{
    const char* exe_from_cmake = "@FS_TEST_EXE_PATH@";
    char exe_from_cal[CAL_BUFFER_LEN] = {0};

    cal_current_exe(
        exe_from_cal,
        sizeof(exe_from_cal)-1
    );
    TEST_ASSERT_EQUAL_STRING(
        exe_from_cmake,
        exe_from_cal
    );
}

static void tmp_dir_test()
{
    const char* tmp_dir = cal_tmp_dir();
    TEST_ASSERT_NOT_NULL(tmp_dir);
    TEST_ASSERT_TRUE(file_exists(tmp_dir));
}

CAL_TEST_MAIN(
    CAL_TEST(appdata_dir_test)
    CAL_TEST(current_exe_test)
    CAL_TEST(tmp_dir_test)
)

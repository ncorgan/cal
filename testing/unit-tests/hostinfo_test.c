/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/platform/hostinfo.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 1024

static void gethostid_test()
{
    long host_id = 0;
    host_id = cal_gethostid();

    // This doesn't hold with Appveyor for some reason...
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    // https://www.appveyor.com/docs/environment-variables/
    char envvar_buffer[BUFFER_LEN] = {0};
    size_t actual_size = 0;
    getenv_s(&actual_size, envvar_buffer, sizeof(envvar_buffer), "APPVEYOR");
    if(!strcmp("True", "APPVEYOR"))
    {
#endif
        TEST_ASSERT_TRUE(host_id > 0);
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    }
#endif
}

static void gethostname_test() {
    char hostname_buffer[BUFFER_LEN] = {0};
    int error_code = cal_gethostname(hostname_buffer, sizeof(hostname_buffer));
    TEST_ASSERT_EQUAL(0, error_code);
    TEST_ASSERT_TRUE(strlen(hostname_buffer) > 0);
}

CAL_TEST_MAIN(
    CAL_TEST(gethostid_test)
    CAL_TEST(gethostname_test)
)

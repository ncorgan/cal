/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/platform/hostinfo.h>

#include <stdio.h>
#include <string.h>

#define BUFFER_LEN 1024

static void hostname_test() {
    char hostname_buffer[BUFFER_LEN] = {0};
    int error_code = cal_hostname(hostname_buffer, sizeof(hostname_buffer));
    TEST_ASSERT_EQUAL(0, error_code);
    TEST_ASSERT_TRUE(strlen(hostname_buffer) > 0);
}

CAL_TEST_MAIN(
    CAL_TEST(hostname_test)
)

/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/platform/process.h>

#include <stdio.h>

static void getpid_test() {
    int pid = cal_getpid();
    TEST_ASSERT_TRUE(pid > 0);
}

static void gettid_test() {
    int tid = cal_gettid();
    TEST_ASSERT_TRUE(tid > 0);
}

CAL_TEST_MAIN(
    CAL_TEST(getpid_test)
    CAL_TEST(gettid_test)
)

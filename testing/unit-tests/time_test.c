/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/time.h>

static void highres_timestamp_test() {
    unsigned long long timestamp1 = cal_highres_timestamp();
    unsigned long long timestamp2 = cal_highres_timestamp();
    TEST_ASSERT_TRUE(timestamp2 >= timestamp1);
}

static void usleep_test() {
    unsigned long long timestamp1 = cal_highres_timestamp();
    cal_usleep(5000); // 5 ms
    unsigned long long timestamp2 = cal_highres_timestamp();
    TEST_ASSERT_TRUE((timestamp2 - timestamp1) >= 5000);
}

CAL_TEST_MAIN(
    CAL_TEST(highres_timestamp_test)
    CAL_TEST(usleep_test)
)

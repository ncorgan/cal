/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/net/ifaddrs.h>

static void ifaddrs_test() {
    int status = 0;
    size_t i = 0;

    struct cal_ifaddrs addrs = {
        .addrs = NULL,
        .length = 0,
        ._internal = NULL
    };

    status = cal_getifaddrs(&addrs);
    TEST_ASSERT_NOT_NULL(addrs.addrs);
    TEST_ASSERT_NOT_EQUAL(0, addrs.length);
    TEST_ASSERT_NOT_NULL(addrs._internal);

    for(size_t i = 0; i < addrs.length; ++i) {
        printf("%s\n", addrs.addrs[i].ifa_name);
    }

    cal_freeifaddrs(&addrs);
    TEST_ASSERT_NULL(addrs.addrs);
    TEST_ASSERT_EQUAL(0, addrs.length);
    TEST_ASSERT_NULL(addrs._internal);
}

CAL_TEST_MAIN(
    CAL_TEST(ifaddrs_test)
)

/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/net/ifaddrs.h>

#include <string.h>

static CAL_INLINE void TEST_ASSERT_STRING_NOT_EMPTY(
    char* str
) {
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_TRUE(strlen(str) > 0);
}

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
        TEST_ASSERT_STRING_NOT_EMPTY(addrs.addrs[i].ifa_name);
        TEST_ASSERT_STRING_NOT_EMPTY(addrs.addrs[i].ifa_addr_str);
        TEST_ASSERT_NOT_NULL(addrs.addrs[i].ifa_addr);
        TEST_ASSERT_NOT_NULL(addrs.addrs[i].ifa_netmask);
        // broadaddr can be null
    }

    cal_freeifaddrs(&addrs);
    TEST_ASSERT_NULL(addrs.addrs);
    TEST_ASSERT_EQUAL(0, addrs.length);
    TEST_ASSERT_NULL(addrs._internal);
}

CAL_TEST_MAIN(
    CAL_TEST(ifaddrs_test)
)

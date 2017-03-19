/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/byteswap.h>

static void byteswap16_test() {
    uint16_t x = 0xABCD;
    uint16_t y = 0xCDAB;
    TEST_ASSERT_EQUAL(y, cal_byteswap16(x));
}

static void byteswap32_test() {
    uint32_t x = 0x1234ABCD;
    uint32_t y = 0xCDAB3412;
    TEST_ASSERT_EQUAL(y, cal_byteswap32(x));
}

static void byteswap64_test() {
    uint64_t x = 0x01234567 | ((uint64_t)(0x89ABCDEF) << 32);
    uint64_t y = 0xEFCDAB89 | ((uint64_t)(0x67452301) << 32);
    TEST_ASSERT_EQUAL(y, cal_byteswap64(x));
}

CAL_TEST_MAIN(
    CAL_TEST(byteswap16_test)
    CAL_TEST(byteswap32_test)
    CAL_TEST(byteswap64_test)
)

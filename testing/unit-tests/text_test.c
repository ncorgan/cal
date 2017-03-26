/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/text.h>

#include <wchar.h>

#define STRBUFFER_LEN 128

const char* strings[] = {
    "ABCDEFG",
    "abcdefg",
    NULL
};

const wchar_t* wstrings[] = {
    L"ABCDEFG",
    L"abcdefg",
    NULL
};

#define TEST_ASSERT_EQUAL_WSTRING(a,b) TEST_ASSERT_EQUAL(0, wcscmp(a,b))

static void mbswcs_utf8_test() {
    char strbuffer[STRBUFFER_LEN] = {0};
    wchar_t wstrbuffer[STRBUFFER_LEN] = {0};
    size_t i = 0;
    int num_chars = 0;

    for(i = 0; strings[i] != NULL && wstrings[i] != NULL; ++i) {
        num_chars = cal_mbstowcs(wstrbuffer, strings[i], STRBUFFER_LEN);
        TEST_ASSERT_EQUAL_WSTRING(wstrings[i], wstrbuffer);

        num_chars = cal_wcstombs(strbuffer, wstrbuffer, STRBUFFER_LEN);
        TEST_ASSERT_EQUAL_STRING(strings[i], strbuffer);
    }
}

CAL_TEST_MAIN(
    CAL_TEST(mbswcs_utf8_test)
)

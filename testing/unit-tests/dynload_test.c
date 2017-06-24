/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/dynload.h>

// Function pointers for what we want to load
typedef int (*add_nums_fcn_t)(int, int);
typedef void (*print_msg_fcn_t)(const char*);
typedef int (*greater_than_five_fcn_t)(int);

static void dynload_test() {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    const char* libname = "dynlib.dll";
    int flags = 0;
#else
    const char* libname = "./libdynlib.so";
    int flags = RTLD_LAZY;
#endif
    void* library_handle = NULL;
    add_nums_fcn_t add_nums = NULL;
    print_msg_fcn_t print_msg = NULL;
    greater_than_five_fcn_t greater_than_five = NULL;
    int result = 0;

    library_handle = cal_loadlibrary(libname, flags);
    TEST_ASSERT_NOT_NULL(library_handle);

    add_nums = cal_getsymbol(library_handle, "add_nums");
    TEST_ASSERT_NOT_NULL(add_nums);
    TEST_ASSERT_EQUAL(5, add_nums(2, 3));

    print_msg = cal_getsymbol(library_handle, "print_msg");
    TEST_ASSERT_NOT_NULL(print_msg);
    print_msg("This is a message");

    greater_than_five = cal_getsymbol(library_handle, "greater_than_five");
    TEST_ASSERT_NOT_NULL(greater_than_five);
    TEST_ASSERT_FALSE(greater_than_five(4));

    result = cal_freelibrary(library_handle);
    TEST_ASSERT_EQUAL(0, result);
}

CAL_TEST_MAIN(
    CAL_TEST(dynload_test)
)

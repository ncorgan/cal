/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <cal/config.h>

#include <stdio.h>

CAL_EXPORT int add_nums(
    int num1,
    int num2
) {
    return (num1 + num2);
}

CAL_EXPORT void print_msg(
    const char* msg
) {
    printf("%s\n", msg);
}

CAL_EXPORT int greater_than_five(
    int num
) {
    return (num > 5) ? 1 : 0;
}

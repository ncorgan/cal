/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef DYNLIB_H
#define DYNLIB_H

#include <cal/config.h>

CAL_EXPORT int add_nums(
    int num1,
    int num2
);

CAL_EXPORT void print_msg(
    const char* msg
);

CAL_EXPORT int greater_than_five(
    int num
);

#endif /* DYNLIB_H */

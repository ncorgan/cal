/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/platform/branch_prediction.h>

int main(int argc, char** argv)
{
    // Unused
    (void)argc;
    (void)argv;

    // No meaningful test, just make sure this test compiles when using
    // the macros.
    if(CAL_LIKELY(1 == 1))
    {
    }
    if(CAL_UNLIKELY(1 == 1))
    {
    }
}
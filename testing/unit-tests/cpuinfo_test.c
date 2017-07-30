/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "cal_test.h"

#include <cal/sys/cpuinfo.h>

#include <stdio.h>

static void cpu_count_test() {
    long cpu_count = cal_cpu_count();
    printf("%ld\n", cpu_count);
}

CAL_TEST_MAIN(
    CAL_TEST(cpu_count_test)
)

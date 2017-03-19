/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_UNITY_H
#define CAL_UNITY_H

#include <Unity/unity.h>

#define CAL_TEST(test_func) \
{ \
    Unity.CurrentTestName = #test_func; \
    ++Unity.NumberOfTests; \
    if(TEST_PROTECT()) { \
        test_func(); \
    } \
    UnityConcludeTest(); \
}

#define CAL_TEST_MAIN(...) \
    int main(int argc, char** argv) { \
        (void)argc; \
        (void)argv; \
        UnityBegin(__FILE__); \
        __VA_ARGS__; \
        return (UnityEnd()); \
    }

#endif /* CAL_UNITY_H */

#
# Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)
#

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# Add small shared library to be loaded in dynload_test
ADD_LIBRARY(dynlib SHARED dynlib/dynlib.c)

IF(WIN32)
    SET(EXE ".exe")
ENDIF()

MACRO(CAL_ADD_TEST name)
    ADD_EXECUTABLE(${name} ${name}.c)
    TARGET_LINK_LIBRARIES(${name} cal unity)
    ADD_TEST(
        ${name} ${CMAKE_CURRENT_BINARY_DIR}/${name}${exe}
    )
ENDMACRO()

SET(cal_tests
    byteswap_test
    dynload_test
    fs_test
    ifaddrs_test
    process_test
    text_test
    time_test
)

FOREACH(test ${cal_tests})
    CAL_ADD_TEST(${test})
ENDFOREACH()

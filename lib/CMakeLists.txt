#
# Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)
#

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

SET(cal_srcs
    net/ifaddrs.c
)
IF(WIN32)
    SET(cal_libs
        iphlpapi
        ntdll
        shlwapi
        ws2_32
    )
ELSE()
    SET(cal_libs
        dl
    )
ENDIF()

SET_SOURCE_FILES_PROPERTIES(${cal_srcs}
    PROPERTIES COMPILE_FLAGS "${CAL_FLAGS}"
)

ADD_LIBRARY(cal STATIC ${cal_srcs})
TARGET_LINK_LIBRARIES(cal ${cal_libs})

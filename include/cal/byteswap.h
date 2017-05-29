/*!
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_BYTESWAP_H
#define CAL_BYTESWAP_H

#include <cal/config.h>

#include <stdint.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#    include <stdlib.h>
#    define CAL_BYTESWAP16(x) _byteswap_ushort(x)
#    define CAL_BYTESWAP32(x) _byteswap_ulong(x)
#    define CAL_BYTESWAP64(x) _byteswap_uint64(x);
#elif defined(CAL_PLATFORM_LINUX)
#    include <byteswap.h>
#    define CAL_BYTESWAP16(x) bswap_16(x)
#    define CAL_BYTESWAP32(x) bswap_32(x)
#    define CAL_BYTESWAP64(x) bswap_64(x);
#elif defined(CAL_PLATFORM_MACOS)
#    include <libkern/OSByteOrder.h>
#    define CAL_BYTESWAP16(x) OSSwapInt16(x)
#    define CAL_BYTESWAP32(x) OSSwapInt32(x)
#    define CAL_BYTESWAP64(x) OSSwapInt64(x)
#else
#    define CAL_BYTESWAP16(x) (uint16_t)(((x & 0xFF) << 8) | (x >> 8))
#    define CAL_BYTESWAP32(x) (uint32_t)((CAL_BYTESWAP16((uint16_t)(x & 0xFFFF)) << 16) | \
                                         (CAL_BYTESWAP16((uint16_t)(x >> 16))))
#    define CAL_BYTESWAP64(x) (uint64_t)((CAL_BYTESWAP32((uint32_t)(x & 0xFFFFFFFF)) << 32) | \
                                         (CAL_BYTESWAP32((uint32_t)(x >> 32))))
#endif

#ifdef __cplusplus
extern "C" {
#endif

static CAL_FORCEINLINE uint16_t cal_byteswap16(uint16_t num) {
    return CAL_BYTESWAP16(num);
}

static CAL_FORCEINLINE uint32_t cal_byteswap32(uint32_t num) {
    return CAL_BYTESWAP32(num);
}

static CAL_FORCEINLINE uint64_t cal_byteswap64(uint64_t num) {
    return CAL_BYTESWAP64(num);
}

#ifdef __cplusplus
}
#endif

#endif

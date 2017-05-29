/*!
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_NET_IFADDRS_H
#define CAL_NET_IFADDRS_H

#include <cal/config.h>

#include <stdlib.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#include <winsock2.h>
#else
#include <sys/types.h>
#endif

struct cal_ifaddr {
    char* ifa_name;

    struct sockaddr* ifa_addr;
    struct sockaddr* ifa_netmask;
    union {
        struct sockaddr* ifu_broadaddr;
        struct sockaddr* ifu_dstaddr;
    };

    char* ifa_addr_str;
    char* ifa_netmask_str;
    union {
        char* ifu_broadaddr_str;
        char* ifu_dstaddr_str;
    };
};

struct cal_ifaddrs {
    struct cal_ifaddr* addrs;
    size_t length;

    void* _internal;
};

#ifdef __cplusplus
extern "C" {
#endif

int cal_getifaddrs(
    struct cal_ifaddrs* addrs
);

void cal_freeifaddrs(
    struct cal_ifaddrs* addrs
);

#ifdef __cplusplus
}
#endif

#endif

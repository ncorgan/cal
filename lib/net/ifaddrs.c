/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <cal/net/ifaddrs.h>

#include <stdio.h>
#include <string.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)

int cal_getifaddrs(
    struct cal_ifaddrs* addrs
) {
    return 0;
}

void cal_freeifaddrs(
    struct cal_ifaddrs* addrs
) {
}

#else

#define _GNU_SOURCE

#include <ifaddrs.h>
#include <netdb.h>

static CAL_INLINE int family_is_inet(
    int family
) {
    return (family == AF_INET || family == AF_INET6);
}

int cal_getifaddrs(
    struct cal_ifaddrs* addrs
) {
    struct ifaddrs *native, *iter;
    int status = 0;
    size_t i = 0;

    if(!addrs) {
        return -1;
    }

    if(getifaddrs((struct ifaddrs**)&addrs->_internal) == -1) {
        return -1;
    }

    native = (struct ifaddrs*)addrs->_internal;

    // Iterate over the internal list and count the number of interfaces
    for(iter = native; iter != NULL; iter = iter->ifa_next) {
        if(iter->ifa_addr && family_is_inet(iter->ifa_addr->sa_family)) {
            ++addrs->length;
        }
    }

    // Point the abstraction's members at the internal representation
    addrs->addrs = calloc(sizeof(struct cal_ifaddr)*addrs->length, 1);
    for(iter = native; iter != NULL; iter = iter->ifa_next) {
        if(iter->ifa_addr && family_is_inet(iter->ifa_addr->sa_family)) {
            addrs->addrs[i].ifa_addr_str = calloc(NI_MAXHOST, 1);
            status = getnameinfo(
                         iter->ifa_addr,
                         (iter->ifa_addr->sa_family == AF_INET) ? sizeof(struct sockaddr_in)
                                                                : sizeof(struct sockaddr_in6),
                         addrs->addrs[i].ifa_addr_str,
                         NI_MAXHOST,
                         NULL,
                         0,
                         NI_NUMERICHOST
                     );

            addrs->addrs[i].ifa_name = iter->ifa_name;
            addrs->addrs[i].ifa_addr = iter->ifa_addr;
            addrs->addrs[i].ifa_netmask = iter->ifa_netmask;
            addrs->addrs[i].ifu_dstaddr = iter->ifa_dstaddr;
            ++i;
        }
    }

    return 0;
}

void cal_freeifaddrs(
    struct cal_ifaddrs* addrs
) {
    size_t i = 0;

    for(i = 0; i < addrs->length; ++i) {
        free(addrs->addrs[i].ifa_addr_str);
    }

    free(addrs->addrs);
    freeifaddrs((struct ifaddrs*)addrs->_internal);

    addrs->addrs = NULL;
    addrs->length = 0;
    addrs->_internal = NULL;
}

#endif

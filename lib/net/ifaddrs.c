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

#include <ifaddrs.h>

int cal_getifaddrs(
    struct cal_ifaddrs* addrs
) {
    struct ifaddrs *native, *iter;
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
        ++addrs->length;
    }

    // Point the abstraction's members at the internal representation
    addrs->addrs = malloc(sizeof(struct cal_ifaddr)*addrs->length);
    iter = native;
    for(i = 0; i < addrs->length && iter != NULL; ++i, iter = native->ifa_next) {
        addrs->addrs[i].ifa_name = iter->ifa_name;
        addrs->addrs[i].ifa_addr = iter->ifa_addr;
        addrs->addrs[i].ifa_netmask = iter->ifa_netmask;
        addrs->addrs[i].ifu_dstaddr = iter->ifa_dstaddr;
    }

    return 0;
}

void cal_freeifaddrs(
    struct cal_ifaddrs* addrs
) {
    free(addrs->addrs);
    freeifaddrs((struct ifaddrs*)addrs->_internal);

    addrs->addrs = NULL;
    addrs->length = 0;
    addrs->_internal = NULL;
}

#endif

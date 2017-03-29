/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <cal/text.h>
#include <cal/net/ifaddrs.h>

#include <stdio.h>
#include <string.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)

#include <iphlpapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define STRING_ALLOC_SIZE 64
#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x)   HeapFree(GetProcessHeap(), 0, (x))

int cal_getifaddrs(
    struct cal_ifaddrs* addrs
) {
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;
    size_t i = 0;
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    ULONG family = AF_UNSPEC; // Both IPv4 and IPv6
    ULONG outBufLen = WORKING_BUFFER_SIZE;
    ULONG iterations = 0;
    PIP_ADAPTER_ADDRESSES native = NULL, iter = NULL;
    PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
    WSADATA wsaData;
    wchar_t* wchar_address = NULL;
    
    if(!addrs) {
        return -1;
    }

    do {
        addrs->_internal = (PIP_ADAPTER_ADDRESSES)MALLOC(outBufLen);
        if(!addrs->_internal) {
            return -1;
        }

        dwRetVal = GetAdaptersAddresses(
                       family,
                       flags,
                       NULL,
                       addrs->_internal,
                       &outBufLen
                   );
        if(dwRetVal == ERROR_BUFFER_OVERFLOW) {
            FREE(addrs->_internal);
            addrs->_internal = NULL;
            ++iterations;
        } else {
            break;
        }
    } while((dwRetVal == ERROR_BUFFER_OVERFLOW) && (iterations < MAX_TRIES));

    native = (PIP_ADAPTER_ADDRESSES)addrs->_internal;

    // Iterate over the internal list and count the number of interfaces
    for(iter = native; iter != NULL; iter = iter->Next) {
        for(pUnicast = iter->FirstUnicastAddress; pUnicast != NULL; pUnicast = pUnicast->Next) {
            ++addrs->length;
        }
    }

    // Point the abstraction's members at the internal representation
    addrs->addrs = calloc(sizeof(struct cal_ifaddr)*addrs->length, 1);
    for(iter = native; iter != NULL; iter = iter->Next) {
        for(pUnicast = iter->FirstUnicastAddress; pUnicast != NULL && i < addrs->length; pUnicast = pUnicast->Next, ++i) {
            addrs->addrs[i].ifa_name = calloc(STRING_ALLOC_SIZE, 1);
            cal_wcstombs(
                addrs->addrs[i].ifa_name,
                iter->FriendlyName,
                STRING_ALLOC_SIZE
            );

            addrs->addrs[i].ifa_addr = pUnicast->Address.lpSockaddr;

            addrs->addrs[i].ifa_addr_str = calloc(STRING_ALLOC_SIZE, 1);
            wchar_address = calloc(sizeof(wchar_t)*STRING_ALLOC_SIZE, 1);
            dwSize = STRING_ALLOC_SIZE;

            // Winsock needs to be initialized for this call.
            WSAStartup(MAKEWORD(2,2), &wsaData);
            dwRetVal = WSAAddressToStringW(
                           addrs->addrs[i].ifa_addr,
                           pUnicast->Address.iSockaddrLength,
                           NULL,
                           wchar_address,
                           &dwSize
                       );
            WSACleanup();

            cal_wcstombs(
                addrs->addrs[i].ifa_addr_str,
                wchar_address,
                STRING_ALLOC_SIZE
            );
            free(wchar_address);
        }
    }

    return (int)dwRetVal;
}

void cal_freeifaddrs(
    struct cal_ifaddrs* addrs
) {
    size_t i = 0;

    for(i = 0; i < addrs->length; ++i) {
        free(addrs->addrs[i].ifa_name);
        free(addrs->addrs[i].ifa_addr_str);
    }

    free(addrs->addrs);
    FREE(addrs->_internal);

    addrs->addrs = NULL;
    addrs->length = 0;
    addrs->_internal = NULL;
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

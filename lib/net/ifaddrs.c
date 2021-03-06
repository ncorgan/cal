/*
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <cal/text.h>
#include <cal/net/ifaddrs.h>

#include <stdint.h>
#include <string.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)

#include <iphlpapi.h>
#include <mstcpip.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define STRING_ALLOC_SIZE 256
#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3

int cal_getifaddrs(
    struct cal_ifaddrs* addrs
)
{
    if(!addrs)
    {
        return -1;
    }

    // Initialize Winsock.
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    size_t iterations = 0;
    DWORD dwRetVal = 0;
    do
    {
        ULONG outBufLen = WORKING_BUFFER_SIZE;
        addrs->_internal = (PIP_ADAPTER_ADDRESSES)malloc(outBufLen);
        if(!addrs->_internal)
        {
            WSACleanup();
            return -1;
        }

        dwRetVal = GetAdaptersAddresses(
                       AF_UNSPEC, // Both IPv4 and IPv6
                       GAA_FLAG_INCLUDE_PREFIX,
                       NULL,
                       addrs->_internal,
                       &outBufLen
                   );
        if(dwRetVal == ERROR_BUFFER_OVERFLOW)
        {
            free(addrs->_internal);
            addrs->_internal = NULL;
            ++iterations;
        }
        else
        {
            break;
        }
    }
    while((dwRetVal == ERROR_BUFFER_OVERFLOW) && (iterations < MAX_TRIES));
    PIP_ADAPTER_ADDRESSES native = (PIP_ADAPTER_ADDRESSES)addrs->_internal;
    PIP_ADAPTER_UNICAST_ADDRESS unicast = NULL;

    // Iterate over the internal list and count the number of interfaces
    for(PIP_ADAPTER_ADDRESSES iter = native; iter != NULL; iter = iter->Next)
    {
        for(unicast = iter->FirstUnicastAddress; unicast != NULL; unicast = unicast->Next)
        {
            ++addrs->length;
        }
    }

    // Point the abstraction's members at the internal representation
    addrs->addrs = calloc(sizeof(struct cal_ifaddr)*addrs->length, 1);

    PIP_ADAPTER_PREFIX prefix = NULL;
    size_t i = 0;
    for(PIP_ADAPTER_ADDRESSES iter = native; iter != NULL; iter = iter->Next)
    {
        for(unicast = iter->FirstUnicastAddress, prefix = iter->FirstPrefix;
            unicast != NULL && prefix != NULL && i < addrs->length;
            unicast = unicast->Next, prefix = prefix->Next, ++i)
        {
            addrs->addrs[i].ifa_name = calloc(STRING_ALLOC_SIZE, 1);
            cal_wcstombs(
                addrs->addrs[i].ifa_name,
                iter->FriendlyName,
                STRING_ALLOC_SIZE
            );

            addrs->addrs[i].ifa_addr = unicast->Address.lpSockaddr;

            addrs->addrs[i].ifa_addr_str = calloc(STRING_ALLOC_SIZE, 1);
            wchar_t* wchar_address = calloc(sizeof(wchar_t)*STRING_ALLOC_SIZE, 1);
            DWORD buf_len = STRING_ALLOC_SIZE;

            dwRetVal = WSAAddressToStringW(
                           addrs->addrs[i].ifa_addr,
                           unicast->Address.iSockaddrLength,
                           NULL,
                           wchar_address,
                           &buf_len
                       );

            cal_wcstombs(
                addrs->addrs[i].ifa_addr_str,
                wchar_address,
                STRING_ALLOC_SIZE
            );
            free(wchar_address);

            // Netmask/prefix.
			addrs->addrs[i].ifa_netmask = calloc(unicast->Address.iSockaddrLength, 1);
            addrs->addrs[i].ifa_netmask->sa_family = addrs->addrs[i].ifa_addr->sa_family;
            if(addrs->addrs[i].ifa_addr->sa_family == AF_INET)
            {
				// IPv4
                LONG mask = 0;
                ConvertLengthToIpv4Mask((ULONG)unicast->OnLinkPrefixLength, &mask);
                addrs->addrs[i].ifa_netmask_str = calloc(STRING_ALLOC_SIZE, 1);
                RtlIpv4AddressToString((const IN_ADDR*)&mask, addrs->addrs[i].ifa_netmask_str);

                wchar_t* wchar_address = calloc(STRING_ALLOC_SIZE, sizeof(wchar_t));
                cal_mbstowcs(
                    wchar_address,
                    addrs->addrs[i].ifa_netmask_str,
                    STRING_ALLOC_SIZE
                );

                WSAStringToAddressW(
                    wchar_address,
                    AF_INET,
                    NULL,
                    addrs->addrs[i].ifa_netmask,
                    &unicast->Address.iSockaddrLength
                );
                free(wchar_address);
            }
            else
            {
                // Source: https://opensource.apple.com/source/mDNSResponder/mDNSResponder-541/mDNSWindows/mDNSWin32.c
                IN6_ADDR mask_inaddr6;
                for(size_t len = (size_t)prefix->PrefixLength, mask_index = 0; len > 0; len -= 8)
                {
                    uint8_t mask_byte = (len >= 8) ? 0xFF : (uint8_t)((0xFFU << (8 - len)) & 0xFFU);
                    mask_inaddr6.s6_addr[mask_index++] = mask_byte;
                }
                for(size_t j = 0; j < 16; ++j)
                {
                    ((struct sockaddr_in6*)(addrs->addrs[i].ifa_netmask))->sin6_addr.s6_addr[j] =
                        ((struct sockaddr_in6*)(addrs->addrs[i].ifa_addr))->sin6_addr.s6_addr[j] & mask_inaddr6.s6_addr[j];
                }

                addrs->addrs[i].ifa_netmask_str = calloc(STRING_ALLOC_SIZE, 1);
                wchar_t* wchar_netmask = calloc(STRING_ALLOC_SIZE, sizeof(wchar_t));

                DWORD buf_len = STRING_ALLOC_SIZE;
                WSAAddressToStringW(
                    (LPSOCKADDR)addrs->addrs[i].ifa_netmask,
                    sizeof(struct sockaddr_in6),
                    NULL,
                    wchar_netmask,
                    &buf_len
                );
                cal_wcstombs(
                    addrs->addrs[i].ifa_netmask_str,
                    wchar_netmask,
                    STRING_ALLOC_SIZE
                );
                free(wchar_netmask);
            }
        }
    }

    WSACleanup();
    return (int)dwRetVal;
}

void cal_freeifaddrs(
    struct cal_ifaddrs* addrs
)
{
    size_t i = 0;

    for(i = 0; i < addrs->length; ++i)
    {
        free(addrs->addrs[i].ifa_name);

        free(addrs->addrs[i].ifa_addr_str);

        // Either both or neither will be null.
        if(addrs->addrs[i].ifa_netmask)
        {
            free(addrs->addrs[i].ifa_netmask);
            free(addrs->addrs[i].ifa_netmask_str);
        }
    }

    free(addrs->addrs);
    free(addrs->_internal);

    addrs->addrs = NULL;
    addrs->length = 0;
    addrs->_internal = NULL;
}

#else

#define _GNU_SOURCE

#include <ifaddrs.h>
#include <netdb.h>

static CAL_FORCEINLINE int family_is_inet(
    int family
)
{
    return (family == AF_INET || family == AF_INET6);
}

int cal_getifaddrs(
    struct cal_ifaddrs* addrs
)
{
    struct ifaddrs *native, *iter;
    size_t i = 0;

    if(!addrs)
    {
        return -1;
    }

    if(getifaddrs((struct ifaddrs**)&addrs->_internal) == -1)
    {
        return -1;
    }

    native = (struct ifaddrs*)addrs->_internal;

    // Iterate over the internal list and count the number of interfaces
    for(iter = native; iter != NULL; iter = iter->ifa_next)
    {
        if(iter->ifa_addr && family_is_inet(iter->ifa_addr->sa_family))
        {
            ++addrs->length;
        }
    }

    // Point the abstraction's members at the internal representation
    addrs->addrs = calloc(sizeof(struct cal_ifaddr)*addrs->length, 1);
    for(iter = native; iter != NULL; iter = iter->ifa_next)
    {
        if(iter->ifa_addr && family_is_inet(iter->ifa_addr->sa_family))
        {
            int status = 0;
            addrs->addrs[i].ifa_name = iter->ifa_name;
            addrs->addrs[i].ifa_addr = iter->ifa_addr;
            addrs->addrs[i].ifa_netmask = iter->ifa_netmask;
            addrs->addrs[i].ifu_dstaddr = iter->ifa_dstaddr;

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
            if(status)
            {
                return status;
            }

            addrs->addrs[i].ifa_netmask_str = calloc(NI_MAXHOST, 1);
            status = getnameinfo(
                         iter->ifa_netmask,
                         (iter->ifa_netmask->sa_family == AF_INET) ? sizeof(struct sockaddr_in)
                                                                   : sizeof(struct sockaddr_in6),
                         addrs->addrs[i].ifa_netmask_str,
                         NI_MAXHOST,
                         NULL,
                         0,
                         NI_NUMERICHOST
                     );
            if(status)
            {
                return status;
            }

            if(addrs->addrs[i].ifu_dstaddr) {
                addrs->addrs[i].ifu_dstaddr_str = calloc(NI_MAXHOST, 1);
                status = getnameinfo(
                             iter->ifa_dstaddr,
                             (iter->ifa_dstaddr->sa_family == AF_INET) ? sizeof(struct sockaddr_in)
                                                                       : sizeof(struct sockaddr_in6),
                             addrs->addrs[i].ifu_dstaddr_str,
                             NI_MAXHOST,
                             NULL,
                             0,
                             NI_NUMERICHOST
                         );
                if(status)
                {
                    return status;
                }
            } else {
                addrs->addrs[i].ifu_dstaddr_str = NULL;
            }

            ++i;
        }
    }

    return 0;
}

void cal_freeifaddrs(
    struct cal_ifaddrs* addrs
)
{
    size_t i = 0;

    for(i = 0; i < addrs->length; ++i)
    {
        free(addrs->addrs[i].ifa_addr_str);
        free(addrs->addrs[i].ifa_netmask_str);
        if(addrs->addrs[i].ifu_dstaddr_str)
        {
            free(addrs->addrs[i].ifu_dstaddr_str);
        }
    }

    free(addrs->addrs);
    freeifaddrs((struct ifaddrs*)addrs->_internal);

    addrs->addrs = NULL;
    addrs->length = 0;
    addrs->_internal = NULL;
}

#endif

/*!
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_TEXT_H
#define CAL_TEXT_H

#include <cal/config.h>

#include <stdlib.h>
#include <wchar.h>

#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
#define _WINSOCKAPI_ // stops windows.h including winsock.h
#include <windows.h>
#else
#include <locale.h>
#include <string.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

static inline int cal_mbstowcs(
    wchar_t* output,
    const char* input,
    size_t num_chars
) {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return MultiByteToWideChar(
               CP_UTF8,
               0,
               input,
               -1,
               output,
               (int)num_chars
           );
#else
    char* old_locale = setlocale(LC_CTYPE, NULL);
    setlocale(LC_CTYPE, "en_us.utf8");
    int ret = mbstowcs(output, input, num_chars);
    if(old_locale) {
        setlocale(LC_CTYPE, old_locale);
    }

    return ret;
#endif
}

static inline int cal_wcstombs(
    char* output,
    const wchar_t* input,
    size_t num_chars
) {
#if defined(CAL_PLATFORM_WIN32) || defined(CAL_PLATFORM_MINGW)
    return WideCharToMultiByte(
               CP_UTF8,
               0,
               input,
               -1,
               output,
               (int)num_chars,
               NULL,
               NULL
           );
#else
    char* old_locale = setlocale(LC_CTYPE, NULL);
    setlocale(LC_CTYPE, "en_us.utf8");
    int ret = wcstombs(output, input, num_chars);
    if(old_locale) {
        setlocale(LC_CTYPE, old_locale);
    }

    return ret;
#endif
}

#ifdef __cplusplus
}
#endif

#endif

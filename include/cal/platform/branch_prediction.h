/*!
 * Copyright (c) 2017 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef CAL_PLATFORM_BRANCH_PREDICTION_H
#define CAL_PLATFORM_BRANCH_PREDICTION_H

#ifdef __GNUC__
#    define CAL_LIKELY(x)   __builtin_expect(!!(x), 1)
#    define CAL_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#    define CAL_LIKELY(x)   (x)
#    define CAL_UNLIKELY(x) (x)
#endif

#endif /* CAL_PLATFORM_BRANCH_PREDICTION_H */
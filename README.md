CAL: C Abstraction Layer
===============================================

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/ncorgan/cal/blob/master/LICENSE.txt)

Every C programmer that's had to maintain compatibility across platforms has had to deal with the headache
of working with implementation differences. Linux vs Windows, POSIX vs WinAPI, the list goes on. This library
aims to ease this issue by providing minimal functions that abstract away these differences, giving users a
single API that can be used across platforms.

Current features:
 * Dynamic library loading
 * Endian-swapping
 * High-frequency timing

README last updated: 2016/03/01

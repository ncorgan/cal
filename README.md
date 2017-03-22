CAL: C Abstraction Layer
===============================================

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/ncorgan/cal/blob/master/LICENSE.txt)
[![Travis-CI Build](https://travis-ci.org/ncorgan/cal.svg)](https://travis-ci.org/ncorgan/cal)
[![AppVeyor Build](https://ci.appveyor.com/api/projects/status/github/ncorgan/cal)](https://ci.appveyor.com/project/ncorgan/cal)

Every C programmer that's had to maintain compatibility across platforms has had to deal with the headache
of working with implementation differences. Linux vs Windows, POSIX vs WinAPI, the list goes on. This library
aims to ease this issue by providing minimal functions that abstract away these differences, giving users a
single API that can be used across platforms.

Current features:
 * Dynamic library loading
 * Endian-swapping
 * Getting common filesystem paths
 * High-frequency timing
 * Text conversion

Testing
-------------------------------------

Using [Travis](https://travis-ci.org/ncorgan/cal) and
[AppVeyor](https://ci.appveyor.com/project/ncorgan/cal), every push to this
repository is automatically tested under the following configurations:

 * Compile, unit test:
   * Ubuntu 14.04 (x64)
     * GCC: 4.8.4, 6.2.0
     * Clang: 3.5.0, 4.0.0
   * Windows Server 2012 R2
     * MSVC (x86, x64): 2010, 2012, 2013, 2015
 * Cross-compile only:
   * MinGW-GCC 4.8.2
   * MSVC (ARM): 2013, 2015

All source files are analyzed with [CppCheck](http://cppcheck.sourceforge.net/).

Unit tests use the [Unity](https://github.com/ThrowTheSwitch/Unity) framework.

README last updated: 2017/03/21

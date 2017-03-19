@setlocal enableextensions enabledelayedexpansion
@echo off

mkdir c:\projects\cal\test-env\build

cd c:\projects\cal\test-env\build
if not !ERRORLEVEL!==0 goto fail

cmake -G "%GENERATOR_NAME%" -DCMAKE_BUILD_TYPE=Release ..\..
if not !ERRORLEVEL!==0 goto fail

msbuild /p:configuration=Release ALL_BUILD.vcxproj
if not !ERRORLEVEL!==0 goto fail

:: Don't run anything when cross-compiling
if "x%GENERATOR_NAME:ARM=%"=="x%GENERATOR_NAME%" (
    ctest --output-on-failure
    if not !ERRORLEVEL!==0 goto fail
)

goto pass

endlocal

:fail
exit /b 1

:pass
exit /b 0

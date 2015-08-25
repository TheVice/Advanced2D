@echo off
setlocal enabledelayedexpansion enableextensions

cl > nul
if %ERRORLEVEL% NEQ 0 goto NO_CL_IN_PATH

cl 2>&1 | findstr /C:"Version 19" > nul && goto MSVC19
cl 2>&1 | findstr /C:"Version 18" > nul && goto MSVC18
cl 2>&1 | findstr /C:"Version 17" > nul && goto MSVC17
cl 2>&1 | findstr /C:"Version 16" > nul && goto MSVC16
cl 2>&1 | findstr /C:"Version 15" > nul && goto MSVC15
cl 2>&1 | findstr /C:"Version 14" > nul && goto MSVC14

goto UNKNOWN_VERSION

:MSVC14
echo Found MSVC14 (Visual Studio 2005)
set MSVC_VER=14
set CMAKE_GENERATOR="Visual Studio 8 2005"
goto VERSION_DETECTED

:MSVC15
echo Found MSVC15 (Visual Studio 2008)
set MSVC_VER=15
set CMAKE_GENERATOR="Visual Studio 9 2008"
goto VERSION_DETECTED

:MSVC16
echo Found MSVC16 (Visual Studio 2010)
set MSVC_VER=16
set CMAKE_GENERATOR="Visual Studio 10"
goto VERSION_DETECTED

:MSVC17
echo Found MSVC17 (Visual Studio 2012)
set MSVC_VER=17
set CMAKE_GENERATOR="Visual Studio 11"
goto VERSION_DETECTED

:MSVC18
echo Found MSVC18 (Visual Studio 2013)
set MSVC_VER=18
set CMAKE_GENERATOR="Visual Studio 12"
goto VERSION_DETECTED

:MSVC19
echo Found MSVC19 (Visual Studio 2015)
set MSVC_VER=19
::Only for cmake 3.1 and above
::For cmake 2.8 and above generator should set to "Visual Studio 12"
::and upgrade solution and projects from console (devenv.exe /upgrade or VCUpgrade.exe) or IDE
set CMAKE_GENERATOR="Visual Studio 14 2015"
goto VERSION_DETECTED

:UNKNOWN_VERSION
set MSVC_VER=XX
echo "***************************"
echo Warning: Unknown MSVC version
echo "***************************"
set CMAKE_GENERATOR="Visual Studio 12"

:VERSION_DETECTED
set CURRENT_DIR=%CD%
if not exist "%CURRENT_DIR%\build" mkdir "%CURRENT_DIR%\build"
if not exist "%CURRENT_DIR%\build\MSVC%MSVC_VER%" mkdir "%CURRENT_DIR%\build\MSVC%MSVC_VER%"
cd "%CURRENT_DIR%\build\MSVC%MSVC_VER%"
cmake %CURRENT_DIR%\src -G %CMAKE_GENERATOR%
cd %CURRENT_DIR%

goto end

:NO_CL_IN_PATH
echo "*****************************************************************************"
echo cl.exe not in the PATH, make sure you are running on 'Developer Command Prompt'
echo "*****************************************************************************"

:end

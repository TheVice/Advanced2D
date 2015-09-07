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

:VERSION_DETECTED
set CURRENT_DIR=%CD%
if not exist "%CURRENT_DIR%\build" mkdir "%CURRENT_DIR%\build"
if not exist "%CURRENT_DIR%\build\MSVC%MSVC_VER%" mkdir "%CURRENT_DIR%\build\MSVC%MSVC_VER%"
cd "%CURRENT_DIR%\build\MSVC%MSVC_VER%"
if [] == [%CMAKE_GENERATOR%] goto DIRECT_CL_BUILD

cmake %CURRENT_DIR%\src -G %CMAKE_GENERATOR%
goto END_BUILD

:DIRECT_CL_BUILD
set CPP_FILES=
for %%x in ("%CURRENT_DIR%\src\Ch\Engine\src\*.cpp") do set CPP_FILES=!CPP_FILES! "%%x"
set CPP_FILES=%CPP_FILES:~1%
cl /analyze /W4 /EHsc /c /GS /D "WIN32" /D "_WINDOWS" /D "_LIB" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" %CPP_FILES% /I "%CURRENT_DIR%\src\Ch\Engine\inc"

set OBJ_FILES=
for %%x in ("%CURRENT_DIR%\build\MSVC%MSVC_VER%\*.obj") do set OBJ_FILES=!OBJ_FILES! "%%x"
set OBJ_FILES=%OBJ_FILES:~1%

lib > nul
if %ERRORLEVEL% NEQ 0 goto NO_LIB
lib %OBJ_FILES% /out:"%CURRENT_DIR%\build\MSVC%MSVC_VER%\Engine.lib"
goto DONE_ENGINE

:NO_LIB
link /lib %OBJ_FILES% /out:"%CURRENT_DIR%\build\MSVC%MSVC_VER%\Engine.lib"

:DONE_ENGINE
::For FMOD 3
set FMOD_LIB=fmodvc.lib
::For FMODEx 4
::set FMOD_LIB=fmodex_vc.lib
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Animation_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Bouncing_Balls.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Collision_Demo_BR.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Collision_Demo_D.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Console_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Font_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\HelloAdvanced2D.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Input_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Lighting_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Math_Test.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\MeshEntity_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Particle_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\RotateAnim_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\RotateScale_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Runtime_Cubes.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\SpriteEntity_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Sprite_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Targeting_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Test_Audio.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Test_Vector3.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS
cl /analyze /W4 /EHsc /GS /D "WIN32" /D "_WINDOWS" /D "DIRECTINPUT_VERSION=0x0800" /D "M_PI=3.14159265358979323846" /D "M_PI_4=0.785398163397448309616" "%CURRENT_DIR%\src\Ch\Samples\Velocity_Demo.cpp" kernel32.lib user32.lib d3d9.lib d3dx9.lib dxguid.lib dinput8.lib winmm.lib Engine.lib "%FMOD_LIB%" /I "%CURRENT_DIR%\src\Ch\Engine\inc" /link /SafeSEH /DynamicBase /NXCompat /SUBSYSTEM:WINDOWS

:END_BUILD
cd %CURRENT_DIR%

goto END

:NO_CL_IN_PATH
echo "*****************************************************************************"
echo cl.exe not in the PATH, make sure you are running on 'Developer Command Prompt'
echo "*****************************************************************************"

:END

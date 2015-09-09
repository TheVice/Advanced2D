Advanced 2D
=======

Fork of source code from "Advanced 2D Game Development by J.S. Harbour" created while study
Addition information can be found at [Game Development Forum » Book Support Area » Advanced 2D Game Development](http://jharbour.com/forum/index.php?board=12.0), original source code can be found [here](http://jharbour.com/wordpress/portfolio/advanced-2d-game-development/) at file ```advanced2d_sources.zip```

###Fork notes
* Original project provide solution for Visual Studio. At fork for create project/solution [cmake](http://www.cmake.org/download/) version 2.8.12 and above are required
* For creating directly Visual Studio 15 solution ```cmake``` version must be 3.1 and above, otherwise you can create solution for previous version and upgrade it to last

###Dependencies
* Windows Platform SDK (some version of Visual Studio have build in)
* Microsoft DirectX SDK (Visual Studio 2012 and above have build in, but project require DXUT that provide only by Microsoft DirectX SDK)
* Audio library [FMOD or FMOD Ex](http://www.fmod.org/download-previous-products/)
  * FMOD version 3 - tested on ```fmodapi375win.zip```, early available at ```http://www.fmod.org/files/fmodapi375win.zip```, with MD5 ```4d28a685a92557c0dac06f9ab2567203``` SHA-1 ```645bc5aa354a1f3932da30e0517c7a1552fc608d``` 
  * FMOD Ex version 4 - original develop for ```FMOD Ex version 4.06.33 (Stable) released on 2007-10-12```, still work with actual ```4.x``` version
* Script library [Lua](https://github.com/rjpcomputing/luaforwindows/releases)
* [Google C++ Testing Framework](https://github.com/google/googletest) - only for tests. In this case you must manual call ```cmake``` and set to it path to ```gtest``` folder. For example if ```gtest``` version ```1.7``` at ```build``` sub directory - call from it will be next ```cmake ..\src -G "Visual Studio 9 2008" -DGTEST_ROOT="build\gtest-1.7.0"``` replace generator name with version of studio that you have

###Building by Visual Studio 2005 and above
* Open ```Developer Command Prompt``` for your version of Visual Studio
* Make sure that path to ```cmake``` bin directory in your PATH variable
* Set enviroment variables ```FMOD_ROOT``` and ```LUA_ROOT``` to binary folders with fmod/fmodex and lua
* Optional you can set ```GTEST_ROOT``` path to gtest source dir
* Locate into project directory
* Type and execute ```msvc.cmd```
* Now at sub directory ```build``` located directory with solution for your version of Visual Studio
* To ```set``` addition ```INCLUDE``` and ```LIB``` directories before call ```msvc.cmd``` do it via console, for example
  * ```set INCLUDE=%INCLUDE%;C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include```
  * ```set INCLUDE=%INCLUDE%;C:\Program Files\Microsoft DirectX SDK (June 2010)\Include```
  * ```set INCLUDE=%INCLUDE%;C:\fmodapi375win\api\inc```
  * ```set INCLUDE=%INCLUDE%;C:\Lua\5.1\include```
  * ```set LIB=%LIB%;C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Lib```
  * ```set LIB=%LIB%;C:\Program Files\Microsoft DirectX SDK (June 2010)\Lib\x86```
  * ```set LIB=%LIB%;C:\fmodapi375win\api\lib```
  * ```set LIB=%LIB%;C:\Lua\5.1\lib```
* Version 2005/2008 have global directory setting so it also possible to set that value via IDE

###Building by other versions of Visual Studio
* If ```msvc.cmd``` script do not determine version of Visual Studio, for example you have Microsoft Visual C++ Toolkit 2003, ```cmake``` do not apply - instead ```cl``` try to build project directly

###Building by Eclipse
* Open ```Command Prompt``` and enter into project directory
* Make sure that path to ```cmake``` bin directory in your PATH variable (```set PATH=%PATH%;"%ProgramFiles(x86)%\cmake-2.8.12.2-win32-x86\bin"``` if you have cmake version 2.8.12.2 at Program Files (x86) on 64 bit version of Windows)
* Make sure that path to MinGW bin directory in your PATH variable 
* Create build sub folder (```mkdir build```) and enter to it (```cd build```)
* Type and execute: ```cmake" ..\src -G "Eclipse CDT4 - MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j%NUMBER_OF_PROCESSORS% -s" -DFMOD_ROOT=<Path to fmod> -DLUA_ROOT=<Path to Lua> -DGTEST_ROOT=<Path to gtest>```
* Project ready for you so you can run Eclipse and import exist project

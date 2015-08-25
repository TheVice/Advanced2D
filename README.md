Advanced 2D
=======

Fork of source code from "Advanced 2D Game Development by J.S. Harbour" created while study
Addition information can be found at [Game Development Forum » Book Support Area » Advanced 2D Game Development](http://jharbour.com/forum/index.php?board=12.0), original source code can be found [here](http://jharbour.com/wordpress/portfolio/advanced-2d-game-development/) at file ```advanced2d_sources.zip```

###Fork notes
* Original project provide solution for Visual Studio. At fork for create project/solution [cmake](http://www.cmake.org/download/) version 2.8.12 and above are required
* For creating directly Visual Studio 15 solution ```cmake``` version must be 3.1 and above, otherwise you can create solution for previous version and upgrade it to last

###Dependencies
* Audio library [FMOD/FMOD Ex](http://www.fmod.org/download-previous-products/) version 3 or 4 for chapter 6 and above
* Script library [Lua](http://lua-users.org/wiki/LuaBinaries) - for chapter 11 and lua based samples
* [Google C++ Testing Framework](https://github.com/google/googletest) - only for tests. In this case you must manual call ```cmake``` and set to it path to ```gtest``` folder. For example if ```gtest``` version ```1.7``` at ```build``` sub directory - call from it will be next ```cmake ..\src -G "Visual Studio 9 2008" -DGTEST_LIBRARY="build\gtest-1.7.0"``` replace generator name with version of studio that you have

###Building by Visual Studio
* Open ```Developer Command Prompt``` for your version of Visual Studio
* Make sure that path to ```cmake``` bin directory in your PATH variable
* Locate into project directory
* Type and execute ```msvc.cmd```
* Now at sub directory ```build``` located directory with solution for your version of Visual Studio
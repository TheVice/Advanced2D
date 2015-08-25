cmake_minimum_required(VERSION 2.8.12)

if(NOT CMAKE_HOST_WIN32)
  message(FATAL_ERROR "This project require Windows host to build and execute")
endif(NOT CMAKE_HOST_WIN32)

project("Advanced 2D")

if(DEFINED ADDITION_INCLUDE_DIRECTORY)
  string(REPLACE "\\" "/" ADDITION_INCLUDE_DIRECTORY ${ADDITION_INCLUDE_DIRECTORY})
  include_directories(SYSTEM ${ADDITION_INCLUDE_DIRECTORY})
endif(DEFINED ADDITION_INCLUDE_DIRECTORY)

if(DEFINED ADDITION_LINK_DIRECTORY)
  string(REPLACE "\\" "/" ADDITION_LINK_DIRECTORY ${ADDITION_LINK_DIRECTORY})
  link_directories(${LINK_DIRECTORIES} ${ADDITION_LINK_DIRECTORY})
endif(DEFINED ADDITION_LINK_DIRECTORY)

set(REQUIRED_LIBRARIES)
list(APPEND REQUIRED_LIBRARIES d3d9)
list(APPEND REQUIRED_LIBRARIES d3dx9)
list(APPEND REQUIRED_LIBRARIES dxguid)
list(APPEND REQUIRED_LIBRARIES dinput8)
list(APPEND REQUIRED_LIBRARIES winmm)

if(NOT MSVC)
  list(APPEND REQUIRED_LIBRARIES pthread)
endif(NOT MSVC)

add_definitions("-DDIRECTINPUT_VERSION=0x0800")

file(GLOB Chapters RELATIVE ${CMAKE_SOURCE_DIR} *)
foreach(Chapter ${Chapters})
if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${Chapter})

  set(chapterPath ${CMAKE_SOURCE_DIR}/${Chapter})

  file(GLOB INC_FILES ${chapterPath}/Engine/inc/*.h)
  file(GLOB CPP_FILES ${chapterPath}/Engine/src/*.cpp)

  set(SRC_FILES)
  list(APPEND SRC_FILES ${C_FILES})
  list(APPEND SRC_FILES ${CPP_FILES})

  set(INC_FOLDER ${chapterPath}/Engine/inc)
  set(libraryName ${Chapter})

  add_library(${libraryName}_ANSI STATIC ${INC_FILES} ${SRC_FILES})
  target_include_directories(${libraryName}_ANSI PRIVATE ${INC_FOLDER})

  if(MSVC)
    add_library(${libraryName}_Unicode STATIC ${INC_FILES} ${SRC_FILES})
    target_include_directories(${libraryName}_Unicode PRIVATE ${INC_FOLDER})
    set_target_properties(${libraryName}_Unicode PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -DUNICODE -D_UNICODE")
  endif(MSVC)

  file(GLOB Samples RELATIVE ${chapterPath}/Samples ${chapterPath}/Samples/*.cpp)
  foreach(Sample ${Samples})
    if(NOT IS_DIRECTORY ${chapterPath}/Samples/${Sample})

      set(sampleName ${Chapter}_${Sample})
      string(REPLACE ".cpp" "" sampleName ${sampleName})

      if(MSVC)
        add_executable(${sampleName}_ANSI WIN32 ${chapterPath}/Samples/${Sample})
        add_executable(${sampleName}_Unicode WIN32 ${chapterPath}/Samples/${Sample})
        set_target_properties(${sampleName}_Unicode PROPERTIES LINK_FLAGS "${LINK_FLAGS} /ENTRY:\"wWinMainCRTStartup\"")
      else()
        add_executable(${sampleName}_ANSI ${chapterPath}/Samples/${Sample})
      endif(MSVC)

      target_link_libraries(${sampleName}_ANSI ${libraryName}_ANSI ${REQUIRED_LIBRARIES})
      target_include_directories(${sampleName}_ANSI PRIVATE ${INC_FOLDER})

      if(MSVC)
        target_link_libraries(${sampleName}_Unicode ${libraryName}_Unicode ${REQUIRED_LIBRARIES})
        target_include_directories(${sampleName}_Unicode PRIVATE ${INC_FOLDER})
        set_target_properties(${sampleName}_Unicode PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -DUNICODE -D_UNICODE")
      endif(MSVC)

    endif(NOT IS_DIRECTORY ${chapterPath}/Samples/${Sample})
  endforeach(Sample ${Samples})

  set(outLocation)
  get_property(outLocation TARGET ${libraryName}_ANSI PROPERTY LOCATION)
  string(FIND ${outLocation} "/" pos REVERSE)
  string(SUBSTRING ${outLocation} 0 ${pos} outLocation)

  file(GLOB resourceFiles RELATIVE ${chapterPath}/ ${chapterPath}/*)
  foreach(resourceFile ${resourceFiles})
    if(NOT IS_DIRECTORY ${chapterPath}/${resourceFile})

      set(target ${outLocation}/${resourceFile})
      set(source ${chapterPath}/${resourceFile})
      add_custom_command(
        TARGET ${libraryName}_ANSI
        COMMAND ${CMAKE_COMMAND} -E copy ${source} ${target}
        DEPENDS ${source}
        COMMENT "Copying ${source} to ${target}"
      )
      message(${source})

    endif(NOT IS_DIRECTORY ${chapterPath}/${resourceFile})
  endforeach(resourceFile ${resourceFiles})

endif(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${Chapter})
endforeach(Chapter ${Chapters})

if(DEFINED GTEST_LIBRARY)
  include(CTest)

  if(BUILD_TESTING)

    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    set(GCOV_LIB)
    if(NOT MSVC)
      set(GCOV_LIB gcov)

      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif(NOT MSVC)

    #TestTimer
    set(SRC_FILES ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Timer.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Timer.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Tests/TestTimer.cpp
                  ${GTEST_LIBRARY}/src/gtest-all.cc
                  ${GTEST_LIBRARY}/src/gtest_main.cc)
    add_executable(TestTimer_ANSI ${SRC_FILES})
    target_include_directories(TestTimer_ANSI PRIVATE ${chapterPath}/Engine/inc ${GTEST_INCLUDE_DIR} ${GTEST_LIBRARY})
    target_link_libraries(TestTimer_ANSI ${REQUIRED_LIBRARIES} ${GCOV_LIB})
    if(MSVC)
      add_executable(TestTimer_Unicode ${SRC_FILES})
      set_target_properties(TestTimer_Unicode PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -DUNICODE -D_UNICODE")
      target_include_directories(TestTimer_Unicode PRIVATE ${chapterPath}/Engine/inc ${GTEST_INCLUDE_DIR} ${GTEST_LIBRARY})
      target_link_libraries(TestTimer_Unicode ${REQUIRED_LIBRARIES} ${GCOV_LIB})
    endif(MSVC)
    #TestTimer

    add_test(TestTimer_ANSI TestTimer_ANSI)
    if(MSVC)
      add_test(TestTimer_Unicode TestTimer_Unicode)
    endif(MSVC)

  endif(BUILD_TESTING)
endif(DEFINED GTEST_LIBRARY)

set(FLAGS)
if(MSVC)
set(FLAGS "${FLAGS} /W4 /GS")
set(LINK_FLAGS "${LINK_FLAGS} /SafeSEH /DynamicBase /NXCompat")
else()
set(FLAGS "${FLAGS} -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unknown-pragmas")
endif(MSVC)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEFAULT_CMAKE_C_FLAGS} ${FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEFAULT_CMAKE_CXX_FLAGS} ${FLAGS}")

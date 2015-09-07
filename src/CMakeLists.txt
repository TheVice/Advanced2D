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

if(DEFINED ENV{FMOD_ROOT})
    string(REPLACE "\\" "/" FMOD_ROOT_DIR $ENV{FMOD_ROOT})
elseif(DEFINED FMOD_ROOT)
    string(REPLACE "\\" "/" FMOD_ROOT_DIR ${FMOD_ROOT})
else()
    message(FATAL_ERROR "Set to FMOD_ROOT path to FMOD 3 or FMODEX 4 dir")
endif()

set(REQUIRED_LIBRARIES d3d9 d3dx9 dxguid dinput8 winmm)

if(EXISTS ${FMOD_ROOT_DIR}/api/fmod.dll)
  if(MSVC)
    list(APPEND REQUIRED_LIBRARIES fmodvc)
  else()
    list(APPEND REQUIRED_LIBRARIES fmod)
  endif(MSVC)
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FMOD_ROOT_DIR}/api/fmod.dll ${CMAKE_BINARY_DIR}/fmod.dll)
elseif(EXISTS ${FMOD_ROOT_DIR}/api/fmodex.dll)
  if(MSVC)
    list(APPEND REQUIRED_LIBRARIES fmodex_vc)
  else()
    list(APPEND REQUIRED_LIBRARIES fmodex)
  endif(MSVC)
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FMOD_ROOT_DIR}/api/fmodex.dll ${CMAKE_BINARY_DIR}/fmodex.dll)
else()
    message(FATAL_ERROR "Unable to find fmod.dll or fmodex.dll")
endif()

include_directories(SYSTEM ${FMOD_ROOT_DIR}/api/inc)
link_directories(${LINK_DIRECTORIES} ${FMOD_ROOT_DIR}/api/lib)

if(NOT MSVC)
  list(APPEND REQUIRED_LIBRARIES pthread)
endif(NOT MSVC)

add_definitions("-DDIRECTINPUT_VERSION=0x0800")
add_definitions("-D_USE_MATH_DEFINES")

file(GLOB Chapters RELATIVE ${CMAKE_SOURCE_DIR} *)
foreach(Chapter ${Chapters})
if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${Chapter})

  set(chapterPath ${CMAKE_SOURCE_DIR}/${Chapter})

  file(GLOB INC_FILES ${chapterPath}/Engine/inc/*.h)
  file(GLOB INL_FILES ${chapterPath}/Engine/inc/*.inl)
  file(GLOB CPP_FILES ${chapterPath}/Engine/src/*.cpp)

  set(SRC_FILES)
  list(APPEND SRC_FILES ${INL_FILES})
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

  file(GLOB resourceFiles RELATIVE ${chapterPath}/ ${chapterPath}/*)
  foreach(resourceFile ${resourceFiles})
    if(NOT IS_DIRECTORY ${chapterPath}/${resourceFile})

      set(target ${CMAKE_BINARY_DIR}/${resourceFile})
      set(source ${chapterPath}/${resourceFile})
      add_custom_command(
        TARGET ${libraryName}_ANSI
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${source} ${target}
        DEPENDS ${source}
        COMMENT "Copying ${source} to ${target}"
      )
      message(${source})

    endif(NOT IS_DIRECTORY ${chapterPath}/${resourceFile})
  endforeach(resourceFile ${resourceFiles})

endif(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${Chapter})
endforeach(Chapter ${Chapters})

if(DEFINED GTEST_ROOT)
  include(CTest)

  if(BUILD_TESTING)
    string(REPLACE "\\" "/" GTEST_ROOT ${GTEST_ROOT})
    set(GTEST_LIBRARY ${GTEST_ROOT})
    set(GTEST_INCLUDE_DIR ${GTEST_ROOT}/include)
    set(GTEST_MAIN_LIBRARY gtest)
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
    list(APPEND REQUIRED_LIBRARIES ${GCOV_LIB})

    #TestAdvanced2d
    set(SRC_FILES ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Advanced2d.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Advanced2d.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Audio.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Audio.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Entity.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Entity.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Input.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Input.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Sprite.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Sprite.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Texture.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Texture.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Timer.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Timer.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Vector3.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Vector3.inl
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Vector3.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Tests/TestAdvanced2d.cpp
                  ${GTEST_LIBRARY}/src/gtest-all.cc
                  ${GTEST_LIBRARY}/src/gtest_main.cc)
    add_executable(TestAdvanced2d_ANSI ${SRC_FILES})
    target_include_directories(TestAdvanced2d_ANSI PRIVATE ${chapterPath}/Engine/inc)
    target_include_directories(TestAdvanced2d_ANSI SYSTEM PRIVATE ${GTEST_INCLUDE_DIR} ${GTEST_LIBRARY})
    target_link_libraries(TestAdvanced2d_ANSI ${REQUIRED_LIBRARIES})
    if(MSVC)
      add_executable(TestAdvanced2d_Unicode ${SRC_FILES})
      set_target_properties(TestAdvanced2d_Unicode PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -DUNICODE -D_UNICODE")
      target_include_directories(TestAdvanced2d_Unicode PRIVATE ${chapterPath}/Engine/inc)
      target_include_directories(TestAdvanced2d_Unicode SYSTEM PRIVATE ${GTEST_INCLUDE_DIR} ${GTEST_LIBRARY})
      target_link_libraries(TestAdvanced2d_Unicode ${REQUIRED_LIBRARIES})
    endif(MSVC)
    #TestAdvanced2d

    #TestParticleEmitter
    set(SRC_FILES ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Advanced2d.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Advanced2d.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Audio.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Audio.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Entity.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Entity.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Input.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Input.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/ParticleEmitter.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/ParticleEmitter.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Sprite.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Sprite.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Texture.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Texture.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Timer.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Timer.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Vector3.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Vector3.inl
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Vector3.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Tests/TestParticleEmitter.cpp
                  ${GTEST_LIBRARY}/src/gtest-all.cc
                  ${GTEST_LIBRARY}/src/gtest_main.cc)
    add_executable(TestParticleEmitter_ANSI ${SRC_FILES})
    target_include_directories(TestParticleEmitter_ANSI PRIVATE ${chapterPath}/Engine/inc)
    target_include_directories(TestParticleEmitter_ANSI SYSTEM PRIVATE ${GTEST_INCLUDE_DIR} ${GTEST_LIBRARY})
    target_link_libraries(TestParticleEmitter_ANSI ${REQUIRED_LIBRARIES})
    if(MSVC)
      add_executable(TestParticleEmitter_Unicode ${SRC_FILES})
      set_target_properties(TestParticleEmitter_Unicode PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -DUNICODE -D_UNICODE")
      target_include_directories(TestParticleEmitter_Unicode PRIVATE ${chapterPath}/Engine/inc)
      target_include_directories(TestParticleEmitter_Unicode SYSTEM PRIVATE ${GTEST_INCLUDE_DIR} ${GTEST_LIBRARY})
      target_link_libraries(TestParticleEmitter_Unicode ${REQUIRED_LIBRARIES})
    endif(MSVC)
    #TestParticleEmitter

    #TestTimer
    set(SRC_FILES ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Timer.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Timer.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Tests/TestTimer.cpp
                  ${GTEST_LIBRARY}/src/gtest-all.cc
                  ${GTEST_LIBRARY}/src/gtest_main.cc)
    add_executable(TestTimer_ANSI ${SRC_FILES})
    target_include_directories(TestTimer_ANSI PRIVATE ${chapterPath}/Engine/inc)
    target_include_directories(TestTimer_ANSI SYSTEM PRIVATE ${GTEST_INCLUDE_DIR} ${GTEST_LIBRARY})
    target_link_libraries(TestTimer_ANSI ${REQUIRED_LIBRARIES})
    if(MSVC)
      add_executable(TestTimer_Unicode ${SRC_FILES})
      set_target_properties(TestTimer_Unicode PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -DUNICODE -D_UNICODE")
      target_include_directories(TestTimer_Unicode PRIVATE ${chapterPath}/Engine/inc)
      target_include_directories(TestTimer_Unicode SYSTEM PRIVATE ${GTEST_INCLUDE_DIR} ${GTEST_LIBRARY})
      target_link_libraries(TestTimer_Unicode ${REQUIRED_LIBRARIES})
    endif(MSVC)
    #TestTimer

    #TestVector3
    set(SRC_FILES ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Vector3.h
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/inc/Vector3.inl
                  ${CMAKE_SOURCE_DIR}/Ch/Engine/src/Vector3.cpp
                  ${CMAKE_SOURCE_DIR}/Ch/Tests/TestVector3.cpp
                  ${GTEST_LIBRARY}/src/gtest-all.cc
                  ${GTEST_LIBRARY}/src/gtest_main.cc)
    add_executable(TestVector3_ANSI ${SRC_FILES})
    target_include_directories(TestVector3_ANSI PRIVATE ${chapterPath}/Engine/inc)
    target_include_directories(TestVector3_ANSI SYSTEM PRIVATE ${GTEST_INCLUDE_DIR} ${GTEST_LIBRARY})
    target_link_libraries(TestVector3_ANSI ${REQUIRED_LIBRARIES})
    if(MSVC)
      set(SRC_FILES ${CMAKE_SOURCE_DIR}/Ch/Tests/TestVector3.cpp
                    ${GTEST_LIBRARY}/src/gtest-all.cc
                    ${GTEST_LIBRARY}/src/gtest_main.cc)
      add_executable(TestVector3_Unicode ${SRC_FILES})
      set_target_properties(TestVector3_Unicode PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -DUNICODE -D_UNICODE")
      target_include_directories(TestVector3_Unicode PRIVATE ${chapterPath}/Engine/inc)
      target_include_directories(TestVector3_Unicode SYSTEM PRIVATE ${GTEST_INCLUDE_DIR} ${GTEST_LIBRARY})
      target_link_libraries(TestVector3_Unicode ${libraryName}_Unicode ${REQUIRED_LIBRARIES})
    endif(MSVC)
    #TestVector3

    add_test(TestAdvanced2d_ANSI TestAdvanced2d_ANSI)
    add_test(TestParticleEmitter_ANSI TestParticleEmitter_ANSI)
    add_test(TestTimer_ANSI TestTimer_ANSI)
    add_test(TestVector3_ANSI TestVector3_ANSI)
    if(MSVC)
      add_test(TestAdvanced2d_Unicode TestAdvanced2d_Unicode)
      add_test(TestParticleEmitter_Unicode TestParticleEmitter_Unicode)
      add_test(TestTimer_Unicode TestTimer_Unicode)
      add_test(TestVector3_Unicode TestVector3_Unicode)
    endif(MSVC)

  endif(BUILD_TESTING)
endif(DEFINED GTEST_ROOT)

if(MSVC)
  set(FLAGS "${FLAGS} /W4 /GS")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEFAULT_CMAKE_C_FLAGS} ${FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEFAULT_CMAKE_CXX_FLAGS} ${FLAGS}")
  set(LINK_FLAGS "${LINK_FLAGS} /SafeSEH /DynamicBase /NXCompat")
else()
  set(FLAGS "${FLAGS} -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unknown-pragmas")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEFAULT_CMAKE_C_FLAGS} ${FLAGS} -std=c11")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEFAULT_CMAKE_CXX_FLAGS} ${FLAGS} -std=c++14")
endif(MSVC)

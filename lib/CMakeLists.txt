cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(AUDIOFILE_LIB ${CMAKE_CURRENT_BINARY_DIR}/lib/libaudiofile.a)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#mingw cross compile option
#set(SYSTEM_NAME CMAKE_SYSTEM_NAME)

if (NOT ${CMAKE_HOST_SYSTEM_NAME} MATCHES ${CMAKE_SYSTEM_NAME})
set (BUILD_FLAG --host=x86_64-w64-mingw32)
endif()

include(ExternalProject)
ExternalProject_Add(libaudiofile
    PREFIX ${${CMAKE_CURRENT_BINARY_DIR}/libaudiofile}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/audiofile
    CONFIGURE_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/audiofile  && ./configure --srcdir=${CMAKE_CURRENT_SOURCE_DIR}/../submodules/audiofile/ --prefix=${CMAKE_CURRENT_BINARY_DIR} --enable-static=yes ${BUILD_FLAG}
 
# && ${CMAKE_MAKE_PROGRAM} distclean

    BUILD_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/audiofile/libaudiofile && ${CMAKE_MAKE_PROGRAM} BUILD_BYPRODUCTS ${AUDIOFILE_LIB}

    INSTALL_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/audiofile/libaudiofile && ${CMAKE_MAKE_PROGRAM} install && echo "DONE"

#echo ""

)

#if (WIN32)
#set (CMAKE_LINKER_FLAGS ${CMAKE_CXX_FLAGS} --export-all-symbols)
#endif()


project(paulstretchlib)

add_definitions(-DKISSFFT)

include_directories(../paulstretch_cpp_modified/)
include_directories(../submodules/paulstretch_cpp/contrib)
include_directories(../submodules/mxml)

include_directories(./compatibility)

set(SOURCES

    PaulstretchLib.cpp
    JSONCodec.cpp

    LiteControl.cpp

    TextFileIO.cpp

    ../paulstretch_cpp_modified/Stretch.cpp
    ../paulstretch_cpp_modified/ProcessedStretch.cpp

    ../paulstretch_cpp_modified/Player.cpp
    ../paulstretch_cpp_modified/PAaudiooutput.cpp

    ../paulstretch_cpp_modified/Control.cpp

    ../paulstretch_cpp_modified/globals.cpp
    ../paulstretch_cpp_modified/BinauralBeats.cpp
    ../paulstretch_cpp_modified/Thread.cpp
    ../paulstretch_cpp_modified/Mutex.cpp

    ../paulstretch_cpp_modified/Input/AInputS.cpp
    ../paulstretch_cpp_modified/Output/AOutputS.cpp

    ../paulstretch_cpp_modified/FreeEdit.cpp
    
    ../submodules/paulstretch_cpp/contrib/kiss_fft.c
    ../submodules/paulstretch_cpp/contrib/kiss_fftr.c

    ../paulstretch_cpp_modified/XMLWrapperDummy.cpp
	
)
if(UNIX)
add_definitions(-DPA_USE_COREAUDIO)
endif(UNIX)

if(MINGW)
#add_definitions(-DPA_USE_WMME=1)

include(FindDSound)
include_directories(${DSOUND_INCLUDE_DIRS})
endif(MINGW)

set(PA_USE_DS OFF CACHE BOOL "ds" FORCE)
set(PA_USE_WDMKS OFF CACHE BOOL "wdmks" FORCE)

add_subdirectory("../submodules/portaudio" "portaudio" EXCLUDE_FROM_ALL)

include_directories(../submodules/audiofile/libaudiofile)



#
set(alac_sources 
  ../submodules/alac/codec/ag_dec.c
  ../submodules/alac/codec/ag_enc.c
  ../submodules/alac/codec/dp_dec.c
  ../submodules/alac/codec/dp_enc.c
  ../submodules/alac/codec/matrix_dec.c
  ../submodules/alac/codec/matrix_enc.c

  ../submodules/alac/codec/ALACBitUtilities.c
  ../submodules/alac/codec/ALACDecoder.cpp
  ../submodules/alac/codec/ALACEncoder.cpp
  ../submodules/alac/codec/EndianPortable.c

  ../submodules/alac/convert-utility/CAFFileALAC.cpp
)

include_directories(../submodules/alac/codec)
include_directories(../submodules/alac/convert-utility)

add_library(ALAC STATIC ${alac_sources})

#
#add_subdirectory("../submodules/ogg" "OGG" EXCLUDE_FROM_ALL)
#option(WITH_OGG OFF)
#add_definitions(-DWITH_OGG=OFF)
set(WITH_OGG OFF CACHE BOOL "ogg" FORCE)
set(BUILD_CXXLIBS OFF CACHE BOOL "flac++" FORCE)
add_subdirectory("../submodules/flac" "FLAC" EXCLUDE_FROM_ALL)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fstack-protector)
set (CMAKE_LINKER_FLAGS ${CMAKE_LINKER_FLAGS} -fstack-protector)

if(UNIX)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
endif(UNIX)

add_library(audiofile STATIC IMPORTED GLOBAL)
add_dependencies(audiofile libaudiofile stdc++ gcc)

set(g711_sources 
  #../submodules/G711/g711.c
  #../submodules/G711/g711_table.c

  ../submodules/audiofile/libaudiofile/g711.c
  ../submodules/audiofile/libaudiofile/extended.c
)

#include_directories(../submodules/G711/)

add_library(G711 STATIC ${g711_sources})

set_target_properties(audiofile PROPERTIES IMPORTED_LOCATION ${AUDIOFILE_LIB} )
#set_target_properties(audiofile PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${AF_INCLUDES})

add_library(paulstretchlib SHARED ${SOURCES})

target_link_libraries(paulstretchlib PRIVATE portaudio)
target_link_libraries(paulstretchlib PRIVATE audiofile)
target_link_libraries(paulstretchlib PRIVATE FLAC)
target_link_libraries(paulstretchlib PRIVATE ALAC)
target_link_libraries(paulstretchlib PRIVATE G711)

add_library(paulstretchlib-static STATIC ${SOURCES})

target_link_libraries(paulstretchlib-static PRIVATE portaudio)
target_link_libraries(paulstretchlib-static PRIVATE audiofile)
target_link_libraries(paulstretchlib-static PRIVATE FLAC)
target_link_libraries(paulstretchlib-static PRIVATE ALAC)
target_link_libraries(paulstretchlib-static PRIVATE G711)



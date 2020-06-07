cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(AUDIOFILE_LIB ${CMAKE_CURRENT_BINARY_DIR}/lib/libaudiofile.a)

include(ExternalProject)
ExternalProject_Add(libaudiofile
    PREFIX ${${CMAKE_CURRENT_BINARY_DIR}/libaudiofile}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/audiofile
    #CONFIGURE_COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/audiofile/configure --srcdir=${CMAKE_CURRENT_SOURCE_DIR}/../submodules/audiofile/ --prefix=${CMAKE_CURRENT_BINARY_DIR} --enable-static=yes 
    CONFIGURE_COMMAND echo "CFG"
    BUILD_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/audiofile/ && ${CMAKE_MAKE_PROGRAM} libaudiofile    BUILD_BYPRODUCTS ${AUDIOFILE_LIB}

    INSTALL_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/audiofile/ && ${CMAKE_MAKE_PROGRAM} libaudiofile && echo "DONE"
#echo ""

)

project(paulstretchlib)

add_definitions(-DKISSFFT)

include_directories(../paulstretch_cpp_modified/)
include_directories(../submodules/paulstretch_cpp/contrib)
include_directories(../submodules/mxml)

include_directories(./compatibility)

set(SOURCES

    PaulstretchLib.cpp
    JSONCodec.cpp

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
#add_definitions(-DPA_USE_WASAPI)
include(FindDSound)
include_directories(${DSOUND_INCLUDE_DIRS})
endif(MINGW)

add_subdirectory("../submodules/portaudio" "build/portaudio" EXCLUDE_FROM_ALL)

include_directories(../submodules/audiofile/libaudiofile)

add_library(paulstretchlib SHARED ${SOURCES})

#add_dependencies(paulstretchlib libaudiofile)

if(UNIX)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
endif(UNIX)

#set(CMAKE_SHARED_LINKER_FLAGS "-libgcc -libstdc++")

add_library(audiofile STATIC IMPORTED GLOBAL)
add_dependencies(audiofile libaudiofile stdc++ gcc)

set_target_properties(audiofile PROPERTIES IMPORTED_LOCATION ${AUDIOFILE_LIB} )

#set_target_properties(audiofile PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${AF_INCLUDES})

target_link_libraries(paulstretchlib PUBLIC portaudio)
target_link_libraries(paulstretchlib PUBLIC audiofile)



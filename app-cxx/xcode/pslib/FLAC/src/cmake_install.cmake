# Install script for directory: /Users/njazz/Documents/github/paulstretchlib/submodules/flac/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/libFLAC/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/share/replaygain_analysis/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/share/replaygain_synthesis/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/share/getopt/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/share/utf8/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/share/grabbag/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/flac/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/metaflac/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/test_libs_common/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/test_libFLAC/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/test_grabbag/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/test_seeking/cmake_install.cmake")
  include("/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/src/test_streams/cmake_install.cmake")

endif()


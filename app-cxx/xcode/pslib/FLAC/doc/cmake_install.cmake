# Install script for directory: /Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/FLAC/html/api" TYPE DIRECTORY FILES "/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/FLAC/doc/html/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/FLAC/html" TYPE FILE FILES
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/images/logo.svg"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/images/logo130.gif"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/changelog.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/developers.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/documentation.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/documentation_bugs.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/documentation_example_code.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/documentation_format_overview.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/documentation_tools.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/documentation_tools_flac.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/documentation_tools_metaflac.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/faq.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/favicon.ico"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/features.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/flac.css"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/format.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/id.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/index.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/license.html"
    "/Users/njazz/Documents/github/paulstretchlib/submodules/flac/doc/html/ogg_mapping.html"
    )
endif()


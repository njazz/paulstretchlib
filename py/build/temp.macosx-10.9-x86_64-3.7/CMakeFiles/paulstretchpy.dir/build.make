# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.16.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.16.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/njazz/Documents/github/paulstretchlib/py

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/njazz/Documents/github/paulstretchlib/py/build/temp.macosx-10.9-x86_64-3.7

# Include any dependencies generated for this target.
include CMakeFiles/paulstretchpy.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/paulstretchpy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/paulstretchpy.dir/flags.make

CMakeFiles/paulstretchpy.dir/module.cpp.o: CMakeFiles/paulstretchpy.dir/flags.make
CMakeFiles/paulstretchpy.dir/module.cpp.o: ../../module.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/njazz/Documents/github/paulstretchlib/py/build/temp.macosx-10.9-x86_64-3.7/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/paulstretchpy.dir/module.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/paulstretchpy.dir/module.cpp.o -c /Users/njazz/Documents/github/paulstretchlib/py/module.cpp

CMakeFiles/paulstretchpy.dir/module.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/paulstretchpy.dir/module.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/njazz/Documents/github/paulstretchlib/py/module.cpp > CMakeFiles/paulstretchpy.dir/module.cpp.i

CMakeFiles/paulstretchpy.dir/module.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/paulstretchpy.dir/module.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/njazz/Documents/github/paulstretchlib/py/module.cpp -o CMakeFiles/paulstretchpy.dir/module.cpp.s

# Object files for target paulstretchpy
paulstretchpy_OBJECTS = \
"CMakeFiles/paulstretchpy.dir/module.cpp.o"

# External object files for target paulstretchpy
paulstretchpy_EXTERNAL_OBJECTS =

../lib.macosx-10.9-x86_64-3.7/paulstretchpy.cpython-37m-darwin.so: CMakeFiles/paulstretchpy.dir/module.cpp.o
../lib.macosx-10.9-x86_64-3.7/paulstretchpy.cpython-37m-darwin.so: CMakeFiles/paulstretchpy.dir/build.make
../lib.macosx-10.9-x86_64-3.7/paulstretchpy.cpython-37m-darwin.so: ../lib.macosx-10.9-x86_64-3.7/libpaulstretchlib.dylib
../lib.macosx-10.9-x86_64-3.7/paulstretchpy.cpython-37m-darwin.so: lib/build/portaudio/libportaudio.a
../lib.macosx-10.9-x86_64-3.7/paulstretchpy.cpython-37m-darwin.so: CMakeFiles/paulstretchpy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/njazz/Documents/github/paulstretchlib/py/build/temp.macosx-10.9-x86_64-3.7/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module ../lib.macosx-10.9-x86_64-3.7/paulstretchpy.cpython-37m-darwin.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/paulstretchpy.dir/link.txt --verbose=$(VERBOSE)
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip -x /Users/njazz/Documents/github/paulstretchlib/py/build/lib.macosx-10.9-x86_64-3.7/paulstretchpy.cpython-37m-darwin.so

# Rule to build all files generated by this target.
CMakeFiles/paulstretchpy.dir/build: ../lib.macosx-10.9-x86_64-3.7/paulstretchpy.cpython-37m-darwin.so

.PHONY : CMakeFiles/paulstretchpy.dir/build

CMakeFiles/paulstretchpy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/paulstretchpy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/paulstretchpy.dir/clean

CMakeFiles/paulstretchpy.dir/depend:
	cd /Users/njazz/Documents/github/paulstretchlib/py/build/temp.macosx-10.9-x86_64-3.7 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/njazz/Documents/github/paulstretchlib/py /Users/njazz/Documents/github/paulstretchlib/py /Users/njazz/Documents/github/paulstretchlib/py/build/temp.macosx-10.9-x86_64-3.7 /Users/njazz/Documents/github/paulstretchlib/py/build/temp.macosx-10.9-x86_64-3.7 /Users/njazz/Documents/github/paulstretchlib/py/build/temp.macosx-10.9-x86_64-3.7/CMakeFiles/paulstretchpy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/paulstretchpy.dir/depend

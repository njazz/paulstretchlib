# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.cmTC_5b4de.Debug:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/CMakeFiles/CMakeTmp/Debug/cmTC_5b4de:
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/CMakeFiles/CMakeTmp/Debug/cmTC_5b4de


PostBuild.cmTC_5b4de.Release:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/CMakeFiles/CMakeTmp/Release/cmTC_5b4de:
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/CMakeFiles/CMakeTmp/Release/cmTC_5b4de


PostBuild.cmTC_5b4de.MinSizeRel:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/CMakeFiles/CMakeTmp/MinSizeRel/cmTC_5b4de:
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/CMakeFiles/CMakeTmp/MinSizeRel/cmTC_5b4de


PostBuild.cmTC_5b4de.RelWithDebInfo:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/CMakeFiles/CMakeTmp/RelWithDebInfo/cmTC_5b4de:
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/CMakeFiles/CMakeTmp/RelWithDebInfo/cmTC_5b4de




# For each target create a dummy ruleso the target does not have to exist

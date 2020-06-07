# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.paulstretch-imgui.Debug:
PostBuild.paulstretchlib.Debug: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/Debug/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui
PostBuild.portaudio.Debug: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/Debug/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/Debug/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui:\
	/usr/local/lib/libSDL2.dylib\
	/usr/local/lib/libSDL2main.a\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/Debug/libpaulstretchlib.dylib\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/Debug/libportaudio.a
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/Debug/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui


PostBuild.paulstretchlib.Debug:
PostBuild.portaudio.Debug: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/Debug/libpaulstretchlib.dylib
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/Debug/libpaulstretchlib.dylib:\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/Debug/libportaudio.a
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/Debug/libpaulstretchlib.dylib


PostBuild.portaudio.Debug:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/Debug/libportaudio.a:
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/Debug/libportaudio.a


PostBuild.paulstretch-imgui.Release:
PostBuild.paulstretchlib.Release: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/Release/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui
PostBuild.portaudio.Release: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/Release/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/Release/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui:\
	/usr/local/lib/libSDL2.dylib\
	/usr/local/lib/libSDL2main.a\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/Release/libpaulstretchlib.dylib\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/Release/libportaudio.a
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/Release/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui


PostBuild.paulstretchlib.Release:
PostBuild.portaudio.Release: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/Release/libpaulstretchlib.dylib
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/Release/libpaulstretchlib.dylib:\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/Release/libportaudio.a
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/Release/libpaulstretchlib.dylib


PostBuild.portaudio.Release:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/Release/libportaudio.a:
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/Release/libportaudio.a


PostBuild.paulstretch-imgui.MinSizeRel:
PostBuild.paulstretchlib.MinSizeRel: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/MinSizeRel/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui
PostBuild.portaudio.MinSizeRel: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/MinSizeRel/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/MinSizeRel/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui:\
	/usr/local/lib/libSDL2.dylib\
	/usr/local/lib/libSDL2main.a\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/MinSizeRel/libpaulstretchlib.dylib\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/MinSizeRel/libportaudio.a
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/MinSizeRel/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui


PostBuild.paulstretchlib.MinSizeRel:
PostBuild.portaudio.MinSizeRel: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/MinSizeRel/libpaulstretchlib.dylib
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/MinSizeRel/libpaulstretchlib.dylib:\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/MinSizeRel/libportaudio.a
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/MinSizeRel/libpaulstretchlib.dylib


PostBuild.portaudio.MinSizeRel:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/MinSizeRel/libportaudio.a:
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/MinSizeRel/libportaudio.a


PostBuild.paulstretch-imgui.RelWithDebInfo:
PostBuild.paulstretchlib.RelWithDebInfo: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/RelWithDebInfo/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui
PostBuild.portaudio.RelWithDebInfo: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/RelWithDebInfo/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/RelWithDebInfo/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui:\
	/usr/local/lib/libSDL2.dylib\
	/usr/local/lib/libSDL2main.a\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/RelWithDebInfo/libpaulstretchlib.dylib\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/RelWithDebInfo/libportaudio.a
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/RelWithDebInfo/paulstretch-imgui.app/Contents/MacOS/paulstretch-imgui


PostBuild.paulstretchlib.RelWithDebInfo:
PostBuild.portaudio.RelWithDebInfo: /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/RelWithDebInfo/libpaulstretchlib.dylib
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/RelWithDebInfo/libpaulstretchlib.dylib:\
	/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/RelWithDebInfo/libportaudio.a
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/RelWithDebInfo/libpaulstretchlib.dylib


PostBuild.portaudio.RelWithDebInfo:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/RelWithDebInfo/libportaudio.a:
	/bin/rm -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/RelWithDebInfo/libportaudio.a




# For each target create a dummy ruleso the target does not have to exist
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/Debug/libpaulstretchlib.dylib:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/MinSizeRel/libpaulstretchlib.dylib:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/RelWithDebInfo/libpaulstretchlib.dylib:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/Release/libpaulstretchlib.dylib:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/Debug/libportaudio.a:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/MinSizeRel/libportaudio.a:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/RelWithDebInfo/libportaudio.a:
/Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/build/portaudio/Release/libportaudio.a:
/usr/local/lib/libSDL2.dylib:
/usr/local/lib/libSDL2main.a:

#!/bin/sh
make -C /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib -f /Users/njazz/Documents/github/paulstretchlib/app-cxx/xcode/pslib/CMakeScripts/paulstretchlib_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all

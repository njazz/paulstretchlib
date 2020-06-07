
mkdir build-win
cd build-win
set CMAKE_C_COMPILER=C:\MinGW\bin\g++
set CMAKE_CXX_COMPILER=C:\MinGW\bin\g++

cmake ..  -G "MinGW Makefiles"
mingw32-make
cd ..
mkdir dist
cp -r build/paulstretch-imgui.exe dist/paulstretch-imgui.exe

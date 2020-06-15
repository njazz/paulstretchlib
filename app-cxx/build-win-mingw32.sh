mkdir build-win-mingw
cd build-win-mingw
cmake .. -DCMAKE_TOOLCHAIN_FILE=cmake/Toolchain-mingw32.cmake
make
cd ..
mkdir dist
cp build-win-mingw/paulstretch-imgui.exe dist/

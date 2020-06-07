
mkdir build-osx
cd build-osx
cmake ..
make
cd ..
mkdir dist
cp -r build/paulstretch-imgui.app dist/paulstretch-imgui.app

# C++ / python bindings for Paulstretch code by Nasca Octavian Paul

Contents:<br>
- "paulstretchlib" in lib/ — original code of the app wrapped as C++ library<br>
- "paulstretchpy" in py/ — python bindings for the library
- c++/imgui app in app-cxx/<br>
- python/imgui app in app-py/<br>

<br>

Library & app extra features:<br>
- multi-threaded batch processing
- JSON file formats for configuration and batch settings

Unsupported original features:<br>
- stretch rate limited to 10000x<br>
- parameter automation not yet implemented<br>
- original XML file support dropped<br>

Roadmap:<br>
- rewrite original code with less dependencies<br>
- automation for all parameters<br>
- automation editor in app<br>

Currently available builds:<br>
- windows (minGW) - FAILS<br>
- linux - not tested<br>
- macOS - OK<br>

![screenshot](screenshot.png)

build:<br><br>
git submodule init<br>
git submodule update<br>
cd lib && mkdir build<br>
cmake ..<br>
make<br>
cd ../../app-cxx<br>
mkdir build<br>
cd build<br>
cmake ..<br>
make

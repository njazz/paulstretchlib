cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.11)

project(paulstretch-imgui)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})

#add_subdirectory(../submodules/SDL-mirror/ "SDL")
#include_directories(../submodules/SDL-mirror/include)

add_subdirectory(../submodules/glfw "GLFW")

include_directories(../submodules/imgui)
include_directories(../submodules/imgui/examples)

include_directories(../submodules/imgui-plot/include)

#include_directories(glew/include)
include_directories(../submodules/imgui/examples/libs/gl3w/)

find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

add_subdirectory(../lib "pslib")
include_directories(../lib)

include_directories(tfd)

include_directories(../submodules/audiofile/libaudiofile)

set(glew_src
../submodules/imgui/examples/libs/gl3w/GL/gl3w.c
)

include_directories(../submodules/glfw/include/)

set(imgui_src

../submodules/imgui/imgui.cpp
../submodules/imgui/imgui_widgets.cpp
../submodules/imgui/imgui_draw.cpp
../submodules/imgui/imgui_demo.cpp

#../submodules/imgui/examples/imgui_impl_sdl.cpp

../submodules/imgui/examples/imgui_impl_glfw.cpp

../submodules/imgui/examples/imgui_impl_opengl2.cpp

../submodules/imgui-plot/src/imgui_plot.cpp

)

set (src
paulstretch-imgui-glfw-gl2.cpp 
UI.cpp
tfd/tinyfiledialogs.c
AFOverview.cpp
)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fstack-protector)
set (CMAKE_LINKER_FLAGS ${CMAKE_LINKER_FLAGS} -fstack-protector)


add_executable(paulstretch-imgui MACOSX_BUNDLE ${src} ${glew_src} ${imgui_src})
set_property(TARGET paulstretch-imgui PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)


if (WIN32)
#set(WIN_LIB stdc++ winpthread ssp gcc)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -Bstatic,--whole-archive -lssp -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

endif()

target_link_libraries(paulstretch-imgui 
glfw

${OPENGL_LIBRARIES} 

${WIN_LIB}

paulstretchlib-static
)

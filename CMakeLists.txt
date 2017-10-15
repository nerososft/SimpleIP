cmake_minimum_required(VERSION 3.6)
project(gp_hw_02)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Board.cpp Board.hpp
        StateBase.cpp StateBase.hpp
        Rectangle.cpp Rectangle.hpp
        PixelMap.cpp PixelMap.h
        ColorRGB.cpp ColorRGB.h
        Pixel.cpp Pixel.h Math.cpp Math.h PNGLoader.cpp PNGLoader.h)



INCLUDE_DIRECTORIES(/usr/local/Cellar/glew/2.0.0/include /usr/local/Cellar/glfw/3.2.1/include /System/Library/Frameworks/OpenGL.framework/Headers)

LINK_DIRECTORIES(/usr/local/Cellar/glew/2.0.0/lib /usr/local/Cellar/glfw/3.2.1/lib /System/Library/Frameworks/OpenGL.framework/Libraries)

LINK_LIBRARIES(gl glew glfw GLU png)


add_executable(gp_hw_02 ${SOURCE_FILES})
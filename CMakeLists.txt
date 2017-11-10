cmake_minimum_required(VERSION 3.6)
project(gp_hw_02)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        #Board.cpp Board.hpp
        StateBase.cpp StateBase.hpp
        Rectangle.cpp Rectangle.hpp
        PixelMap.cpp PixelMap.h
        ColorRGB.cpp ColorRGB.h
        Pixel.cpp Pixel.h
        Math.cpp Math.h
        PNGLoader.cpp PNGLoader.h
        Font.cpp Font.h
        JPEGLoader.cpp JPEGLoader.h
        filter/Fliter.cpp filter/Fliter.h
        FpsLimter.cpp FpsLimter.h
        System.cpp System.h
        rl/ValueIteration.cpp
        rl/ValueIteration.h rl/PolicyIteration.cpp
        rl/PolicyIteration.h rl/RandomPolicyIteration.cpp
        rl/RandomPolicyIteration.h rl/Action.cpp rl/Action.h
        rl/TerminalState.cpp rl/TerminalState.h
        segmentation/Segmentation.cpp segmentation/Segmentation.h
        segmentation/Line.cpp segmentation/Line.h
        Go.cpp Go.h MTC/MTC.cpp MTC/MTC.h MTC/MTCNode.cpp MTC/MTCNode.h network/HttpService.cpp network/HttpService.h)

INCLUDE_DIRECTORIES(/usr/local/Cellar/glew/2.0.0/include
        /usr/local/Cellar/glfw/3.2.1/includes
        /System/Library/Frameworks/OpenGL.framework/Headers
        /usr/local/Cellar/freetype/2.7.1/include/freetype2
        )

LINK_DIRECTORIES(/usr/local/Cellar/glew/2.0.0/lib
        /usr/local/Cellar/glfw/3.2.1/lib
        /System/Library/Frameworks/OpenGL.framework/Libraries
        /usr/local/Cellar/freetype/2.7.1/lib)

LINK_LIBRARIES(gl glew glfw GLU png freetype)

#fuck
add_executable(gp_hw_02 ${SOURCE_FILES})
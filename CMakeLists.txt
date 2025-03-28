﻿cmake_minimum_required(VERSION 3.29.6)
project(SDL)

set(CMAKE_CXX_STANDARD 20)

link_directories(lib)

add_executable(SDL main.cpp
        include/SDL/Window.hpp
        include/SDL/Vector.hpp
        include/SDL/Color.hpp
        include/SDL/Renderer.hpp
        src/Renderer.cpp
        include/SDL/Drawable.hpp
        include/SDL/Vertex.hpp
        src/Window.cpp
        src/Color.cpp
        include/SDL/Shapes.hpp
        include/SDL/Init.hpp
        src/Init.cpp
        include/SDL/Event.hpp
        include/SDL/Rect.hpp
        include/SDL/Timer.hpp
        src/Timer.cpp
        src/Vertex.cpp
        src/Shapes.cpp
        include/SDL/FramerateLimiter.hpp
        src/FramerateLimiter.cpp
        include/SDL/Matrix.hpp
        include/SDL/Transformable.hpp
        include/SDL/Shape.hpp
        src/Shape.cpp
        include/SDL/Transform.hpp
        src/Transform.cpp
        src/Transformable.cpp
        include/SDL/Texture.hpp
        src/Texture.cpp
        include/SDL/Error.hpp
        src/Error.cpp
        include/SDL/Surface.hpp
        src/Surface.cpp
        include/SDL/Properties.hpp
        src/Properties.cpp
        include/SDL/APIObject.hpp
        include/SDL/Angle.hpp
        include/SDL/Math.hpp
        src/Math.cpp
)
target_include_directories(SDL PUBLIC include)
target_link_libraries(SDL SDL3 SDL3_image)
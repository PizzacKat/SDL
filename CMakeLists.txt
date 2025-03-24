cmake_minimum_required(VERSION 3.29.6)
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
)
target_include_directories(SDL PUBLIC include)
target_link_libraries(SDL SDL3 SDL3_image)
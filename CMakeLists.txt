cmake_minimum_required(VERSION 3.29.6)
project(SDLPP VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

link_directories(lib)

set(SDL_SRC
        src/Renderer.cpp
        src/Window.cpp
        src/Color.cpp
        src/Init.cpp
        src/Timer.cpp
        src/Vertex.cpp
        src/Shapes.cpp
        src/FramerateLimiter.cpp
        src/Shape.cpp
        src/Transform.cpp
        src/Transformable.cpp
        src/Texture.cpp
        src/Error.cpp
        src/Surface.cpp
        src/Properties.cpp
        src/Math.cpp
)

set(SDL_HEADERS include/SDLPP/Angle.hpp
        include/SDLPP/APIObject.hpp
        include/SDLPP/Color.hpp
        include/SDLPP/Drawable.hpp
        include/SDLPP/Error.hpp
        include/SDLPP/Event.hpp
        include/SDLPP/FramerateLimiter.hpp
        include/SDLPP/Init.hpp
        include/SDLPP/Math.hpp
        include/SDLPP/Matrix.hpp
        include/SDLPP/Properties.hpp
        include/SDLPP/Rect.hpp
        include/SDLPP/Renderer.hpp
        include/SDLPP/Timer.hpp
        include/SDLPP/Shape.hpp
        include/SDLPP/Shapes.hpp
        include/SDLPP/Surface.hpp
        include/SDLPP/Transformable.hpp
        include/SDLPP/Transform.hpp
        include/SDLPP/Texture.hpp
        include/SDLPP/Vector.hpp
        include/SDLPP/Vertex.hpp
        include/SDLPP/Window.hpp
        include/SDLPP/SDLPP.hpp
)

include(GNUInstallDirs)

add_library(SDLPP ${SDL_SRC} ${SDL_HEADERS})
target_link_libraries(SDLPP SDL3 SDL3_image)
target_include_directories(SDLPP
        PRIVATE src
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(SDLPP PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
)

install(TARGETS SDLPP EXPORT SDLPPConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/)

export(TARGETS SDLPP FILE SDLPPConfig.cmake)
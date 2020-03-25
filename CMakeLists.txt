cmake_minimum_required(VERSION 3.15)
project(ProjectRPG)

set(CMAKE_CXX_STANDARD 17)
 
include_directories(.)
set(CMAKE_CXX_FLAGS "-Wall -Wextra  -Wstrict-aliasing -pedantic -fmax-errors=5 -Werror -Wunreachable-code -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option ${CMAKE_CXX_FLAGS}")

add_executable(ProjectRPG 
    Tile.hpp
    GameUI.hpp
    GameUI.cpp
    Map.cpp
    Engine.cpp
    TextureManager.cpp
    Main.cpp
    Hud.cpp
    Entity/Player.cpp 
    Entity/Player.hpp 
    Entity/Actor.hpp 
    Graphics/Spritesheet.hpp 
    Graphics/Spritesheet.cpp
    World/WorldManager.hpp
    World/WorldManager.cpp
        )

if(MSVC) 
target_link_libraries(ProjectRPG sfml-graphics-d sfml-system-d sfml-window-d)
endif(MSVC)

if(UNIX) 
target_link_libraries(ProjectRPG -lsfml-graphics -lsfml-system -lsfml-window)
endif(UNIX)
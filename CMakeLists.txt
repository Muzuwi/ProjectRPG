cmake_minimum_required(VERSION 3.15)
project(ProjectRPG)

set(CMAKE_CXX_STANDARD 17)
 
include_directories(.)

add_executable(ProjectRPG
    World/Tile.hpp
    Interface/GameUI.hpp
    Interface/GameUI.cpp
    Interface/InvUI.hpp
    Interface/InvUI.cpp
    Interface/StatUI.hpp
    Interface/StatUI.cpp
    Interface/SettUI.hpp
    Interface/SettUI.cpp
    Interface/Hud.hpp
    Interface/Hud.cpp
    Interface/Button.hpp
    Interface/Button.cpp
    World/Map.cpp
    Engine.cpp
    Graphics/TextureManager.cpp
    Main.cpp
    Entity/Player.cpp 
    Entity/Player.hpp 
    Entity/Actor.hpp 
    Graphics/Spritesheet.hpp 
    Graphics/Spritesheet.cpp
    World/WorldManager.hpp
    World/WorldManager.cpp
    Entity/Actor.cpp
    Entity/NPC.cpp
    Entity/NPC.hpp
    Entity/Script.cpp
    Entity/Script.hpp)

if(MSVC) 
target_link_libraries(ProjectRPG sfml-graphics-d sfml-system-d sfml-window-d lua53)
endif(MSVC)

if(UNIX) 
target_link_libraries(ProjectRPG -lsfml-graphics -lsfml-system -lsfml-window -llua)
endif(UNIX)
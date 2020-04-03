cmake_minimum_required(VERSION 3.15)
project(ProjectRPG)

set(CMAKE_CXX_STANDARD 17)
 
include_directories(.)

add_library(RPGBase
        World/Map.cpp
        Graphics/TextureManager.cpp
        Entity/Player.cpp
        Graphics/Spritesheet.cpp
        World/WorldManager.cpp
        Entity/Actor.cpp
        Entity/NPC.cpp
        Entity/Script.cpp
        World/TileSet.cpp
        )


add_executable(ProjectRPG
    Interface/GameUI.cpp
    Interface/InvUI.cpp
    Interface/StatUI.cpp
    Interface/SettUI.cpp
    Interface/Hud.cpp
    Interface/Button.cpp
    Interface/Window.cpp
    Engine.cpp
    Main.cpp
        )

if(MSVC) 
target_link_libraries(ProjectRPG RPGBase sfml-graphics-d sfml-system-d sfml-window-d lua53)
endif(MSVC)

if(UNIX) 
target_link_libraries(ProjectRPG RPGBase -lsfml-graphics -lsfml-system -lsfml-window -llua)
endif(UNIX)

add_subdirectory(Tools/)

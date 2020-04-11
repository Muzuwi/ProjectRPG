cmake_minimum_required(VERSION 3.15)
project(ProjectRPG)

set(CMAKE_CXX_STANDARD 17)
 
include_directories(.)

add_library(RPGBase
        World/Map.cpp
        Entity/Player.cpp
        Graphics/Spritesheet.cpp
        World/WorldManager.cpp
        Entity/Actor.cpp
        Entity/NPC.cpp
        Entity/Script.cpp
        World/TileSet.cpp
        JsonOverloads.cpp
        Sound/SoundEngine.cpp
        Item.cpp
        Interface/DialogEngine.cpp
        "Interface/Components/Window.cpp"
        AssetManager.cpp
        World/Item.cpp
        )


add_executable(ProjectRPG
    Interface/GameUI.cpp
    "Interface/Inventory/InvUI.cpp"
    "Interface/Statistics/StatUI.cpp"
    "Interface/Settings/SettUI.cpp"
    Interface/Hud.cpp
    "Interface/Components/Button.cpp"
    "Interface/Components/Window.cpp"
    "Interface/Components/Frame.cpp"
    "Interface/Inventory/Cell.cpp"
    "Interface/Inventory/ItemUI.cpp"
    Engine.cpp
    Main.cpp
    )

if(MSVC) 
target_link_libraries(ProjectRPG RPGBase sfml-audio-d sfml-graphics-d sfml-system-d sfml-window-d lua53)
endif(MSVC)

if(UNIX) 
target_link_libraries(ProjectRPG RPGBase -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -llua)
endif(UNIX)

add_subdirectory(Tools/)

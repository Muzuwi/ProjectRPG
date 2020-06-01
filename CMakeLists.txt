cmake_minimum_required(VERSION 3.15)
project(ProjectRPG)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_library(Extern
    Entity/Script.cpp
    JsonOverloads.cpp
)

add_library(Resource
    AssetManager.cpp
    Sound/SoundEngine.cpp
    Graphics/Spritesheet.cpp
)

add_library(Interface
    Interface/GameUI.cpp
    Interface/DialogEngine.cpp
    Interface/Hud.cpp
    Interface/Components/Window.cpp
    Interface/Components/Slider.cpp
    Interface/Components/Switch.cpp
    Interface/Components/RawWindow.cpp
    Interface/Components/Button.cpp
    Interface/Components/Window.cpp
    Interface/Components/Frame.cpp
    Interface/Components/Slider.cpp
    Interface/Components/Switch.cpp
    Interface/Components/RawWindow.cpp
    Interface/Inventory/Cell.cpp
    Interface/Inventory/InvUI.cpp
    Interface/Inventory/ItemUI.cpp
    Interface/Settings/SettUI.cpp
)

add_library(RPGBase
    Entity/Actor.cpp
    Entity/Player.cpp
    Entity/NPC.cpp
    World/Item.cpp
    World/Map.cpp
    World/TileSet.cpp
    World/WorldManager.cpp
)


add_executable(ProjectRPG
    Engine.cpp
    Main.cpp
)

target_link_libraries(ProjectRPG
    RPGBase
    Extern
    Resource
    Interface
)

if(MSVC)
target_link_libraries(ProjectRPG sfml-audio-d sfml-graphics-d sfml-system-d sfml-window-d lua53)
endif(MSVC)

if(UNIX)
target_link_libraries(ProjectRPG -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -llua)
endif(UNIX)

add_subdirectory(Tools/)

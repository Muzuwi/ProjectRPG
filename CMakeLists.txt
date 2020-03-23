cmake_minimum_required(VERSION 3.15)
project(ProjectRPG)

set(CMAKE_CXX_STANDARD 17)
 
include_directories(.)

add_executable(ProjectRPG 
        Tile.cpp
        Map.cpp
        Engine.cpp
        TextureManager.cpp
        Main.cpp
        Entity/Player.cpp 
	    Entity/Player.hpp 
	    Entity/Actor.hpp 
	    Graphics/Spritesheet.hpp 
	    Graphics/Spritesheet.cpp)

target_link_libraries(ProjectRPG sfml-graphics sfml-system sfml-window)

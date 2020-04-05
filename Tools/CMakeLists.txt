include_directories(imgui/)
include_directories(.)

add_library(ImGui
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui-SFML.cpp
        imgui/imgui.cpp
        )

add_executable(RPGEditor
        EditWindow.cpp
        Editor.cpp
        Tool.hpp Brush.hpp TilePicker.hpp CursorTool.hpp NPCCreator.hpp)

find_library(OpenGL OpenGL GL)
add_dependencies(RPGEditor RPGBase ImGui)

if(MSVC)
    target_link_libraries(RPGEditor opengl32 RPGBase ImGui sfml-audio-d sfml-graphics-d sfml-system-d sfml-window-d lua53)
endif(MSVC)

if(UNIX)
    target_link_libraries(RPGEditor OpenGL RPGBase ImGui -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -llua)
endif(UNIX)
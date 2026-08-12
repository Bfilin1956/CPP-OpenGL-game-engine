cmake_minimum_required(VERSION 4.1)

project(atta_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(thirdparty/SDL2)
add_subdirectory(thirdparty/assimp)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/glew)

add_library(imgui STATIC
        thirdparty/imgui/imgui.cpp
        thirdparty/imgui/imgui_draw.cpp
        thirdparty/imgui/imgui_tables.cpp
        thirdparty/imgui/imgui_widgets.cpp
)

target_include_directories(imgui PUBLIC
        thirdparty/imgui
)

find_package(OpenGL REQUIRED)

add_subdirectory(Engine)

add_executable(atta_game
        main.cpp
)

target_link_libraries(atta_game PRIVATE
        engine
)
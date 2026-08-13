file(GLOB_RECURSE ENGINE_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(engine STATIC
        ${ENGINE_SOURCES}
        Resources/ResourceManager.cpp
        Resources/ResourceManager.h
        Core/Time.cpp
        Core/Time.h

)

target_include_directories(engine
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_include_directories(engine
        PUBLIC
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_SOURCE_DIR}/thirdparty/stb"
)
target_link_libraries(engine
        PUBLIC
        SDL2::SDL2
        glm::glm
        imgui
        glew
        OpenGL::GL
        assimp::assimp
)
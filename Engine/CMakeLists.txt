file(GLOB_RECURSE ENGINE_SOURCES
        CONFIGURE_DEPENDS
        *.cpp
)

add_library(engine ${ENGINE_SOURCES}
        ModelLoader.cpp
        ModelLoader.h
        Model.h
        Texture.h)

target_include_directories(engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine PUBLIC
        SDL2::SDL2
        SDL2::SDL2main
        glm::glm
        imgui::imgui
        ${GLEW_LIBRARIES}
        OpenGL::GL
        assimp
)
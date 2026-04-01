cmake_minimum_required(VERSION 4.1)
cmake_minimum_required(VERSION 3.22)
project(atta_game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# зависимости
find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)
# движок как отдельная библиотека
add_subdirectory(Engine)

# исполняемый файл
add_executable(atta_game main.cpp)

target_link_libraries(atta_game PRIVATE
        engine
)
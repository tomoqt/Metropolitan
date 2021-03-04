add_subdirectory("shaders")

find_package(OpenGL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/Grafica/include)
add_executable(GUIMetro Grafica.cpp src/glad.c src/shader.cpp)

target_link_libraries(GUIMetro glfw OpenGL::GL)

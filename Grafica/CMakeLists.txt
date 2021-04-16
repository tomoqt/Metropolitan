add_subdirectory("shaders")

find_package(OpenGL REQUIRED)

add_executable(GUIMetro Grafica.cpp src/glad.c src/shader.cpp src/datiInput.cpp src/manager.cpp src/texture.cpp)
target_include_directories(GUIMetro PUBLIC ${PROJECT_SOURCE_DIR}/Grafica/include)

target_link_libraries(GUIMetro  PUBLIC glfw OpenGL::GL)

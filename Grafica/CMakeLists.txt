find_package(OpenGL REQUIRED)

add_executable(GUIMetro Grafica.cpp)

target_link_libraries(GUIMetro glfw OpenGL::GL)

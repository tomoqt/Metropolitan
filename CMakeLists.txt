cmake_minimum_required (VERSION 3.12)

project ("Metropolitan")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Include sub-projects.
add_subdirectory("glfw-3.3.3")
add_subdirectory ("Grafica")
add_subdirectory ("outputGA")

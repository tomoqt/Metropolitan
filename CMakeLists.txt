cmake_minimum_required (VERSION 3.12)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project ("Metropolitan")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Include sub-projects.
add_subdirectory("glfw-3.3.3")
add_subdirectory("Grafica")
add_subdirectory("outputGA")
add_subdirectory("GA")
add_subdirectory("Images")

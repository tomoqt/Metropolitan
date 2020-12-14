cmake_minimum_required (VERSION 3.12)

set(FLTK_DIR "c:/fltk-1.3.5/CMake/")

find_package(FLTK REQUIRED NO_MODULE)

add_executable(GUIMetro WIN32 "CMakeProject1.cpp")

target_include_directories(GUIMetro PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(GUIMetro fltk)

cmake_minimum_required (VERSION 3.12)

set(FLTK_DIR C:/fltk-1.3.5/build)
find_package(FLTK REQUIRED NO_MODULE)

include_directories(${FLTK_INCLUDE_DIRS})

add_executable(GUIMetro WIN32 CMakeProject1.cpp)

# target_include_directories(GUIMetro PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(GUIMetro fltk)

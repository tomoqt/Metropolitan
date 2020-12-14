set(FLTK_DIR C:/fltk-1.3.5/build)
find_package(FLTK REQUIRED NO_MODULE)

add_executable(GUIMetro CMakeProject1.cpp)

target_include_directories(GUIMetro PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(GUIMetro fltk fltk_gl)

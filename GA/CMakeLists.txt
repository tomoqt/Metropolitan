file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/algoritmo_genetico.py"
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/algoritmo_genetico.py"
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
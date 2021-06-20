add_subdirectory(graphics/src)

set(SOURCES main.c opcje.c game.c score.c)

add_executable(${PROJECT} ${SOURCES})

target_link_libraries(${PROJECT} tet_graphics)
add_library(Game game.cc)

include_directories(include)
link_directories(${UCS_BINARY_DIR})

add_executable(main main.cc)

target_link_libraries(main Game)

add_subdirectory(test)

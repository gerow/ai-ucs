find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})

add_library(Game game.cc)

include_directories(include)
link_directories(${UCS_BINARY_DIR})

add_executable(main main.cc)

target_link_libraries(main Game ${Boost_LIBRARIES})

add_subdirectory(test)

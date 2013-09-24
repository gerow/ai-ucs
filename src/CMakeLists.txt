find_package(Boost)

if(NOT Boost_INCLUDE_DIR)
  set(Boost_INCLUDE_DIR "/auto/usc/boost/default/include/boost-1_32")
  set(Boost_LIBRARIES "/auto/usc/boost/default/lib")
endif(NOT Boost_INCLUDE_DIR)

include_directories(${Boost_INCLUDE_DIR})

add_library(Game game.cc)

include_directories(include)
link_directories(${UCS_BINARY_DIR})

add_executable(main main.cc)

target_link_libraries(main Game ${Boost_LIBRARIES})

add_subdirectory(test)

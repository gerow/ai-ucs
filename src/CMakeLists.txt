find_package(Boost)

if(${Boost_INCLUDE_DIR} EQUAL NOTFOUND)
  set(Boost_INCLUDE_DIR "/auto/usc/boost/default/include")
  set(Boost_LIBRARIES "/auto/usc/boost/default/lib")
endif(${Boost_INCLUDE_DIR} EQUAL NOTFOUND)

include_directories(${Boost_INCLUDE_DIR})

add_library(Game game.cc)

include_directories(include)
link_directories(${UCS_BINARY_DIR})

add_executable(main main.cc)

target_link_libraries(main Game ${Boost_LIBRARIES})

add_subdirectory(test)

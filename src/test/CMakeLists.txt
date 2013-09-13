include_directories(${UCS_SOURCE_DIR}/lib/gtest/include)

add_library(GameTest test_game.cc)

add_executable(test_all test_all.cc)

target_link_libraries(test_all gtest GameTest)

add_test(TestAll test_all)

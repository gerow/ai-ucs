include_directories(${UCS_SOURCE_DIR}/lib/gtest/include)

add_executable(test_all test_all.cc test_game.cc)

target_link_libraries(test_all gtest Game)

add_test(TestAll test_all)

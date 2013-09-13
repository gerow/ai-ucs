#include "gtest/gtest.h"
#include "ai-ucs/game.h"

TEST(GameTest, TestConstructsProperly) {
  Game g(5, 5, 1, 2, 3, 4);

  ASSERT_EQ(5, g.w());
  ASSERT_EQ(5, g.h());
  ASSERT_EQ(1, g.x1());
  ASSERT_EQ(2, g.y1());
  ASSERT_EQ(3, g.x2());
  ASSERT_EQ(4, g.y2());
}
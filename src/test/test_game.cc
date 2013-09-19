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

TEST(GameTest, TestCopyConstructor) {
  Game g(5, 5, 1, 2, 3, 4);
  Game g2(g);

  ASSERT_EQ(5, g2.w());
  ASSERT_EQ(5, g2.h());
  ASSERT_EQ(1, g2.x1());
  ASSERT_EQ(2, g2.y1());
  ASSERT_EQ(3, g2.x2());
  ASSERT_EQ(4, g2.y2());
}

TEST(GameTest, TestMovesUpProperly) {
  Game g(5, 5, 1, 2, 3, 4);

  g.move(Game::UP);
  ASSERT_EQ(1, g.x1());
  ASSERT_EQ(1, g.y1());
  ASSERT_EQ(4, g.x2());
  ASSERT_EQ(4, g.y2());
}

TEST(GameTest, TestMovesUpProperlyAtWall) {
  Game g(5, 5, 1, 1, 3, 4);

  g.move(Game::UP);
  ASSERT_EQ(1, g.y1());
}

TEST(GameTest, TestMovesRightProperly) {
  Game g(5, 5, 1, 2, 3, 4);

  g.move(Game::RIGHT);
  ASSERT_EQ(2, g.x1());
  ASSERT_EQ(2, g.y1());
  ASSERT_EQ(3, g.x2());
  ASSERT_EQ(5, g.y2());
}

TEST(GameTest, TestMovesRightProperlyAtWall) {
  Game g(5, 5, 5, 1, 3, 4);

  g.move(Game::RIGHT);
  ASSERT_EQ(5, g.x1());
}

TEST(GameTest, TestMovesDownProperly) {
  Game g(5, 5, 1, 2, 3, 4);

  g.move(Game::DOWN);
  ASSERT_EQ(1, g.x1());
  ASSERT_EQ(3, g.y1());
  ASSERT_EQ(2, g.x2());
  ASSERT_EQ(4, g.y2());
}

TEST(GameTest, TestMovesDownProperlyAtWall) {
  Game g(5, 5, 5, 5, 3, 4);

  g.move(Game::DOWN);
  ASSERT_EQ(5, g.y1());
}

TEST(GameTest, TestMovesLeftProperly) {
  Game g(5, 5, 2, 3, 4, 5);

  g.move(Game::LEFT);
  ASSERT_EQ(1, g.x1());
  ASSERT_EQ(3, g.y1());
  ASSERT_EQ(4, g.x2());
  ASSERT_EQ(4, g.y2());
}

TEST(GameTest, TestMovesLeftProperlyAtWall) {
  Game g(5, 5, 1, 1, 3, 4);

  g.move(Game::LEFT);
  ASSERT_EQ(1, g.x1());
}

TEST(GameTest, TestMoveCostIsCorrect) {
  Game g(5, 5, 1, 1, 3, 4);

  ASSERT_EQ(3, g.move_cost(Game::UP));
  ASSERT_EQ(5, g.move_cost(Game::RIGHT));
  ASSERT_EQ(6, g.move_cost(Game::DOWN));
  ASSERT_EQ(4, g.move_cost(Game::LEFT));
}
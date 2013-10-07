#include "gtest/gtest.h"
#include "ai-ucs/game.h"

#include <math.h>

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
  Game g(5, 5, 2, 2, 3, 4);

  g.move(Game::UP);
  ASSERT_EQ(1, g.x1());
  ASSERT_EQ(2, g.y1());
  ASSERT_EQ(3, g.x2());
  ASSERT_EQ(5, g.y2());
}

TEST(GameTest, TestMovesUpProperlyAtWall) {
  Game g(5, 5, 1, 1, 3, 4);

  g.move(Game::UP);
  ASSERT_EQ(1, g.x1());
}

TEST(GameTest, TestMovesRightProperly) {
  Game g(5, 5, 1, 2, 3, 4);

  g.move(Game::RIGHT);
  ASSERT_EQ(1, g.x1());
  ASSERT_EQ(3, g.y1());
  ASSERT_EQ(4, g.x2());
  ASSERT_EQ(4, g.y2());
}

TEST(GameTest, TestMovesRightProperlyAtWall) {
  Game g(5, 5, 5, 5, 3, 4);

  g.move(Game::RIGHT);
  ASSERT_EQ(5, g.y1());
}

TEST(GameTest, TestMovesDownProperly) {
  Game g(5, 5, 1, 2, 3, 4);

  g.move(Game::DOWN);
  ASSERT_EQ(2, g.x1());
  ASSERT_EQ(2, g.y1());
  ASSERT_EQ(3, g.x2());
  ASSERT_EQ(3, g.y2());
}

TEST(GameTest, TestMovesDownProperlyAtWall) {
  Game g(5, 5, 5, 5, 3, 4);

  g.move(Game::DOWN);
  ASSERT_EQ(5, g.x1());
}

TEST(GameTest, TestMovesLeftProperly) {
  Game g(5, 5, 2, 3, 4, 5);

  g.move(Game::LEFT);
  ASSERT_EQ(2, g.x1());
  ASSERT_EQ(2, g.y1());
  ASSERT_EQ(3, g.x2());
  ASSERT_EQ(5, g.y2());
}

TEST(GameTest, TestMovesLeftProperlyAtWall) {
  Game g(5, 5, 1, 1, 3, 4);

  g.move(Game::LEFT);
  ASSERT_EQ(1, g.y1());
}

TEST(GameTest, TestMoveCostIsCorrect) {
  Game g(5, 5, 1, 1, 3, 4);

  ASSERT_EQ(3, g.move_cost(Game::UP));
  ASSERT_EQ(5, g.move_cost(Game::RIGHT));
  ASSERT_EQ(6, g.move_cost(Game::DOWN));
  ASSERT_EQ(4, g.move_cost(Game::LEFT));
}

TEST(GameTest, TestLoadFromFile) {
  boost::shared_ptr<Game> g = Game::load("src/test/files/test_input.txt");

  ASSERT_EQ(7, g.get()->w());
  ASSERT_EQ(7, g.get()->h());

  ASSERT_EQ(1, g.get()->x1());
  ASSERT_EQ(5, g.get()->y1());

  ASSERT_EQ(3, g.get()->x2());
  ASSERT_EQ(7, g.get()->y2());
}

TEST(GameTest, TestKeepsHistory) {
  Game g(5, 5, 2, 2, 3, 4);

  g.move(Game::UP);

  ASSERT_TRUE(g.state_in_history(2, 2, 3, 4));
  ASSERT_FALSE(g.state_in_history(1, 2, 3, 8));
}

TEST(GameTest, TestKeepsCost) {
  Game g(5, 5, 1, 2, 3, 4);

  g.move(Game::RIGHT);

  ASSERT_EQ(5, g.cost());
}

TEST(GameTest, TestPriorityQueue) {
  game_priority_queue q;

  Game *g = new Game(5, 5, 5, 5, 5, 5);
  Game *g2 = new Game(5, 5, 1, 1, 1, 1);
  Game *g3 = new Game(5, 5, 2, 2, 2, 2);

  g2->move(Game::RIGHT);
  // g3 should have a higher cost
  g3->move(Game::DOWN);

  q.push(boost::shared_ptr<Game>(g3));
  q.push(boost::shared_ptr<Game>(g));
  q.push(boost::shared_ptr<Game>(g2));

  ASSERT_EQ(g->cost(), 0);
  ASSERT_EQ(g2->cost(), 5);

  ASSERT_EQ(5, q.top()->x1());
  q.pop();
  ASSERT_EQ(1, q.top()->x1());
  q.pop();
  // expect it to be 3 since we moved down, incrmenting the x1 value
  ASSERT_EQ(3, q.top()->x1());
}

TEST(GameTest, TestMovesRightProperly2) {
  Game g(7, 7, 1, 5, 5, 7);

  g.move(Game::RIGHT);

  ASSERT_EQ(1, g.x1());
  ASSERT_EQ(6, g.y1());
  ASSERT_EQ(6, g.x2());
  ASSERT_EQ(7, g.y2());
}

TEST(GameTest, TestCopyConstructor2) {
  Game *g = new Game(7, 7, 1, 5, 3, 7);
  Game *g2 = new Game(*g);

  g2->move(Game::RIGHT);

  ASSERT_EQ(1, g->x1());
  ASSERT_EQ(5, g->y1());
  ASSERT_EQ(3, g->x2());
  ASSERT_EQ(7, g->y2());

  ASSERT_EQ(1, g2->x1());
  ASSERT_EQ(6, g2->y1());
  ASSERT_EQ(4, g2->x2());
  ASSERT_EQ(7, g2->y2());

  delete g;
  delete g2;
}

TEST(GameTest, TestEuclidianDistance) {
  Game g(7, 7, 1, 1, 2, 2);
  Game g2(7, 7, 1, 1, 5, 3);

  ASSERT_EQ(sqrt(2.0), g.euclidian_distance());
  ASSERT_EQ(sqrt(20.0), g2.euclidian_distance());
}

TEST(GameTest, TestCanberraDistance) {
  Game g(7, 7, 1, 1, 2, 2);
  Game g2(7, 7, 1, 2, 3, 4);

  ASSERT_EQ(2.0/3.0, g.canberra_distance());
  ASSERT_EQ((2.0/4.0) + (2.0/6.0), g2.canberra_distance());
}

#include "ai-ucs/game.h"

#include <boost/shared_ptr.hpp>
#include <queue>

int
main(int argc, char** argv)
{
  boost::shared_ptr<Game> g = Game::load("input.txt");

  return 0;
}


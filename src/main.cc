#include "ai-ucs/game.h"

#include <boost/shared_ptr.hpp>
#include <queue>

int
main(int argc, char** argv)
{
  std::cout << "Loading input.txt from current working directory...\n";
  boost::shared_ptr<Game> g = Game::load("input.txt");
  std::cout << "Done!\n";

  game_priority_queue q;

  q.push(g);
  boost::shared_ptr<Game> g2 = q.top();
  q.pop();
  while (!q.empty()) {
    // grab an element from the queue and pop
    // it off
    boost::shared_ptr<Game> cur = q.top();
    q.pop();

    // see if it is a solution
    if (cur->is_game_won()) {
      std::cout << "Solution found!\n";
      // if it is, then we can save it to
      // output.txt and return
      std::cout << "Saving trace to output.txt\n";
      //cur->save("output.txt");
      std::cout << "Done!\n";
      return 0;
    }

    // otherwise, expand this node and put it
    // on the tree
    Game::Move moves[4] = {Game::RIGHT, Game::LEFT, Game::DOWN, Game::UP};
    for (int i = 0; i < sizeof moves; i++) {
      // make a copy of the candidate
      boost::shared_ptr<Game> candidate = boost::shared_ptr<Game>(new Game(*cur.get()));
      // apply the move
      candidate->move(moves[i]);
      if (!cur->state_in_history(candidate->x1(), candidate->y1(), candidate->x2(), candidate->y2())) {
        // if the new state is not in the history then throw
        // it into the queue
        q.push(candidate);
      }
    }
  }

  std::cout << "No solution\n";

  return 0;
}

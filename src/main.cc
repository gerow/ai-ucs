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
  while (!q.empty()) {
    // grab an element from the queue and pop
    // it off
    boost::shared_ptr<Game> cur = q.top();
    q.pop();

    // see if it is a solution
    std::cout << "Seeing if ("
        << cur->x1() << ","
        << cur->y1() << ") ("
        << cur->x2() << ","
        << cur->y2() << ") is a solution\n";
    std::cout << "This has a cost of " << cur->cost() << "\n";
    if (cur->is_game_won()) {
      std::cout << "Solution found!\n";
      std::cout << "It has a total cost of " << cur->cost() << "\n";
      // if it is, then we can save it to
      // output.txt and return
      std::cout << "Saving trace to output.txt\n";
      cur->save("output.txt");
      std::cout << "Done!\n";
      return 0;
    }

    // otherwise, expand this node and put it
    // on the tree
    Game::Move moves[4] = {Game::RIGHT, Game::LEFT, Game::DOWN, Game::UP};
    for (int i = 0; i < 4; i++) {
      std::cout << "move " << i << " is " << moves[i] << "\n";
      // make a copy of the candidate
      boost::shared_ptr<Game> candidate = boost::shared_ptr<Game>(new Game(*cur));

      // apply the move
      if (!candidate->move(moves[i])) {
        // if it isn't a valid move then continue
        continue;
      }
      std::cout << "Seeing if ("
        << candidate->x1() << ","
        << candidate->y1() << ") ("
        << candidate->x2() << ","
        << candidate->y2() << ") is a viable candidate\n";

      std::cout << "It is\n";
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

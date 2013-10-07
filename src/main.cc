#include "ai-ucs/game.h"

#include <boost/shared_ptr.hpp>
#include <queue>

template <class T>
void
solve(T q, boost::shared_ptr<Game> game, int &expanded, boost::shared_ptr<Game> solution)
{
  expanded = 0;

  q.push(game);

  while (!q.empty()) {
    boost::shared_ptr<Game> cur = q.top();
    q.pop();
    expanded++;

    if (cur->is_game_won()) {
      *solution = *cur;
      return;
    }
    Game::Move moves[4] = {Game::RIGHT, Game::LEFT, Game::DOWN, Game::UP};
    for (int i = 0; i < 4; i++) {
      boost::shared_ptr<Game> candidate = boost::shared_ptr<Game>(new Game(*cur));
      if (!candidate->move(moves[i])) {
        // if it isn't valid continue
        continue;
      }

      if (!cur->state_in_history(candidate->x1(), candidate->y1(), candidate->x2(), candidate->y2())) {
        // if the new state is not in the history then throw
        // it into the queue
        q.push(candidate);
      }
    }
  }
}

int
main(int argc, char** argv)
{
  std::cout << "Loading input.txt from current working directory...\n";
  boost::shared_ptr<Game> g = Game::load("input.txt");
  std::cout << "Done!\n";

  game_priority_queue q;

  euclidian_priority_queue eq;
  int e_expanded = 0;
  boost::shared_ptr<Game> e_solution(new Game);
  canberra_priority_queue cq;
  int c_expanded = 0;
  boost::shared_ptr<Game> c_solution(new Game);
  knight_priority_queue kq;
  int k_expanded = 0;
  boost::shared_ptr<Game> k_solution(new Game);

  solve(eq, g, e_expanded, e_solution);
  solve(cq, g, c_expanded, c_solution);
  solve(kq, g, k_expanded, k_solution);

  std::cout << "Nodes Expanded\n";
  std::cout << "Euclidian Canberra Knight\n";
  std::cout << e_expanded << " " << c_expanded << " " << k_expanded << "\n";

  e_solution->save("output.txt");

  /*
  // first do euclidian
  q.push(g);
  while (!eq.empty()) {
    // grab an element from the queue and pop
    // it off
    boost::shared_ptr<Game> cur = eq.top();
    eq.pop();

    e_expanded++;

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
      //cur->save("output.txt");
      e_solution = cur;
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

  g->save_no_solution("output.txt");

  return 0;
  */
}

#include "ai-ucs/game.h"

#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
#include <queue>
#include <fstream>
#include <iomanip>

template <class T>
bool
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
      return true;
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

  expanded = -1;
  return false;
}

int
main(int argc, char** argv)
{
  std::cout << "Loading input.txt from current working directory...\n";
  boost::shared_ptr<std::vector<boost::shared_ptr<Game> > > g = Game::load("input.txt");
  std::cout << "Done!\n";

  game_priority_queue q;

  euclidian_priority_queue eq;
  std::vector<int> e_expanded;
  for (int i = 0; i < 3; i++) {
    e_expanded.push_back(0);
  }
  std::vector<boost::shared_ptr<Game> > e_solution;
  std::vector<bool> e_found;
  for (int i = 0; i < 3; i++) {
    e_solution.push_back(boost::shared_ptr<Game>(new Game));
  }
  canberra_priority_queue cq;
  std::vector<int> c_expanded;
  for (int i = 0; i < 3; i++) {
    c_expanded.push_back(0);
  }
  std::vector<boost::shared_ptr<Game> > c_solution;
  std::vector<bool> c_found;
  for (int i = 0; i < 3; i++) {
    c_solution.push_back(boost::shared_ptr<Game>(new Game));
  }
  knight_priority_queue kq;
  std::vector<int> k_expanded;
  for (int i = 0; i < 3; i++) {
    k_expanded.push_back(0);
  }
  std::vector<boost::shared_ptr<Game> > k_solution;
  std::vector<bool> k_found;
  for (int i = 0; i < 3; i++) {
    k_solution.push_back(boost::shared_ptr<Game>(new Game));
  }

  for (int i = 0; i < 3; i++) {
    if (solve(eq, (*g)[i], e_expanded[i], e_solution[i])) {
      e_found.push_back(true);
    } else {
      e_found.push_back(false);
    }
    if (solve(cq, (*g)[i], c_expanded[i], c_solution[i])) {
      c_found.push_back(true);
    } else {
      c_found.push_back(false);
    }
    if (solve(kq, (*g)[i], k_expanded[i], k_solution[i])) {
      k_found.push_back(true);
    } else {
      k_found.push_back(false);
    }

    while (!eq.empty()) {
      eq.pop();
    }
    while (!cq.empty()) {
      cq.pop();
    }
    while (!kq.empty()) {
      kq.pop();
    }
  }

  // alright, now we should have some solutions!
  std::ofstream o;
  o.open("output.txt");

  // this should give us a nice tabular output
  o << std::setw(20);

  o << "Nodes Expanded" << std::endl;
  // lead with an empty string to give us 20 characters to
  // make things look nice and tabular
  o << boost::format("%-10s %-10s %-10s %-10s\n") % "" % "Euclidian" % "Canberra" % "Knight";
  for (int i = 0; i < 3; i++) {
    std::ostringstream os;
    os << "Input" << i;

    std::ostringstream e_o;
    std::ostringstream c_o;
    std::ostringstream k_o;
    if (e_expanded[i] == -1) {
      e_o << "-";
    } else {
      e_o << e_expanded[i];
    }
    std::string c_str;
    if (c_expanded[i] == -1) {
      c_o << "-";
    } else {
      c_o << c_expanded[i];
    }
   std::string k_str;
    if (k_expanded[i] == -1) {
      k_o << "-";
    } else {
      k_o << k_expanded[i];
    } 

    o << boost::format("%-10s %-10s %-10s %-10s\n") % os.str() % e_o.str() % c_o.str() % k_o.str();
  }

  // now we find the optimal path solutions and print them out
  #define E_PATH 0
  #define C_PATH 1
  #define K_PATH 2

  o.close();

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

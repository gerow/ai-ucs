#include <ai-ucs/game.h>

#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

Game::Game() :
  _w(0),
  _h(0),
  _cost(0)
{
  _players[0] = player_vector(2);
  _players[1] = player_vector(2);

  _history[0] = std::vector<boost::shared_ptr<player_vector> >();
  _history[1] = std::vector<boost::shared_ptr<player_vector> >();
}

Game::Game(int w, int h, int x1, int y1, int x2, int y2) :
  _w(w),
  _h(h),
  _cost(0)
{
  _players[0] = player_vector(2);
  _players[1] = player_vector(2);

  _history[0] = std::vector<boost::shared_ptr<player_vector> >();
  _history[1] = std::vector<boost::shared_ptr<player_vector> >();

  _players[0](0) = x1;
  _players[0](1) = y1;
  _players[1](0) = x2;
  _players[1](1) = y2;
}

Game::Game(Game &g) :
  _w(g._w),
  _h(g._h),
  _cost(g._cost)
{
  _players[0] = g._players[0];
  _players[1] = g._players[1];
  _history[0] = g._history[0];
  _history[1] = g._history[1];
}

boost::shared_ptr<std::vector<boost::shared_ptr<Game> > >
Game::load(std::string filename)
{
  int size, x1, y1, x2, y2;
  std::ifstream f;
  f.open(filename.c_str());

  boost::shared_ptr<std::vector<boost::shared_ptr<Game> > > out(new std::vector<boost::shared_ptr<Game> >());

  for (int i = 0; i < 3; i++) {
    f >> size;
    f >> x1;
    f >> y1;
    f >> x2;
    f >> y2;

    out->push_back(boost::shared_ptr<Game>(new Game(size, size, x1, y1, x2, y2)));
  }

  f.close();

  return out;
}

bool
Game::move(Game::Move m)
{
  // first, throw the current position into
  // the history vector
  save_to_history();
  if (!move_player(0, m)) {
    return false;
  }
  if (m == Game::RIGHT) {
    if (!move_player(1, Game::DOWN)) {
      return false;
    }
  } else if (m == Game::LEFT) {
    if (!move_player(1, Game::UP)) {
      return false;
    }
  } else if (m == Game::DOWN) {
    if (!move_player(1, Game::LEFT)) {
      return false;
    }
  } else if (m == Game::UP) {
    if (!move_player(1, Game::RIGHT)) {
      return false;
    }
  }

  _cost += move_cost(m);

  return true;
}

int
Game::move_cost(Game::Move m)
{
  return 2;
}

bool
Game::is_game_won()
{
  return _players[0](0) == _players[1](0) &&
         _players[0](1) == _players[1](1);
}

int
Game::w()
{
  return _w;
}

int
Game::h()
{
  return _h;
}

int
Game::x1()
{
  return _players[0](0);
}

int
Game::y1()
{
  return _players[0](1);
}

int
Game::x2()
{
  return _players[1](0);
}

int
Game::y2()
{
  return _players[1](1);
}

double
Game::x1d()
{
  return (double) _players[0](0);
}

double
Game::y1d()
{
  return (double) _players[0](1);
}

double
Game::x2d()
{
  return (double) _players[1](0);
}

double
Game::y2d()
{
  return (double) _players[1](1);
}

//std::vector<boost::shared_ptr<player_vector> >
//Game::history()
//{
//  return _history;
//}

int
Game::cost()
{
  return _cost;
}

void
Game::save(std::string filename)
{
  std::ofstream f;
  f.open(filename.c_str());

  f << _cost << "\n";

  for (int i = 0; i < _history[0].size(); i++) {
    f << (*_history[0][i])(0) << " "
      << (*_history[0][i])(1) << "\n";
  }

  f << x1() << " " << y1() << "\n";

  f.close();
}

void
Game::save_no_solution(std::string filename)
{
  std::ofstream f;
  f.open(filename.c_str());

  f << -1 << "\n";

  f.close();
}

double
Game::euclidian_distance()
{
  double answer_squared = pow((x2d() - x1d()), 2) + pow((y2d() - y1d()), 2);
  return sqrt(answer_squared);
}

double
Game::canberra_distance()
{
  double x_frac = abs(x2d() - x1d()) / (x2d() + x1d());
  double y_frac = abs(y2d() - y1d()) / (y2d() + y1d());

  return x_frac + y_frac;
}

int
Game::knight_distance()
{
  // this lookup table only works for any move less than
  // 9 rows or 9 ranks away, but it should be enough for our
  // problem
  //
  // The alternative is to use a breadth first search to find out
  // the answer, but heuristics are kinda supposed to be fast, and
  // doing that would defeat the purpose. So we use breadth first
  // search to generate this table instead.
  static const char kn_lookup[81] = {
    0, 3, 2, 3, 2, 3, 4, 5, 4,
    3, 2, 1, 2, 3, 4, 3, 4, 5,
    2, 1, 4, 3, 2, 3, 4, 5, 4,
    3, 2, 3, 2, 3, 4, 3, 4, 5,
    2, 3, 2, 3, 4, 3, 4, 5, 4,
    3, 4, 3, 4, 3, 4, 5, 4, 5,
    4, 3, 4, 3, 4, 5, 4, 5, 6,
    5, 4, 5, 4, 5, 4, 5, 6, 5,
    4, 5, 4, 5, 4, 5, 6, 5, 6 
  };

  int vx, vy;

  vx = abs(x1() - x2());
  vy = abs(y1() - y2());

  return kn_lookup[vx + vy * 9];
}

bool
Game::move_player(int player, Game::Move m)
{
  if (m == Game::RIGHT && _players[player][1] < _w) {
    _players[player][1]++;
  } else if (m == Game::LEFT && _players[player][1] > 1) {
    _players[player][1]--;
  } else if (m == Game::DOWN && _players[player][0] < _h) {
    _players[player][0]++;
  } else if (m == Game::UP && _players[player][0] > 1) {
    _players[player][0]--;
  } else {
    return false;
  }

  return true;
}

double
Game::astar(Heuristic h)
{
  double heuristic;

  if (h == EUCLIDIAN) {
    std::cout << "Heuristic is euclidian\n";
    heuristic = euclidian_distance();
  } else if (h == CANBERRA) {
    std::cout << "Heuristic is canberra\n";
    heuristic = canberra_distance();
  } else if (h == KNIGHT) {
    std::cout << "Heuristic is knight\n";
    heuristic = knight_distance();
  }

  std::cout << "this cost heuristic is " << (_cost + heuristic) << "\n";

  if (is_game_won()) {
    std::cout << "this is a potential solution!\n";
  }
  return _cost + heuristic;
}

void
Game::save_to_history()
{
  boost::shared_ptr<player_vector> old_player_1 = boost::shared_ptr<player_vector>(new player_vector(_players[0]));
  boost::shared_ptr<player_vector> old_player_2 = boost::shared_ptr<player_vector>(new player_vector(_players[1]));
  _history[0].push_back(old_player_1);
  _history[1].push_back(old_player_2);
}

bool
Game::state_in_history(int x1, int y1, int x2, int y2)
{
  for (int i = 0; i < _history[0].size(); i++) {
    if ((*_history[0][i].get())(0) == x1 &&
        (*_history[0][i].get())(1) == y1 &&
        (*_history[1][i].get())(0) == x2 &&
        (*_history[1][i].get())(1) == y2) {
      return true;
    }
  }

  return false;
}

GameComparison::GameComparison(const bool& revparam)
{
  _reverse = revparam;
}

bool
GameComparison::operator()(const boost::shared_ptr<Game> &lhs, const boost::shared_ptr<Game> &rhs) const
{
  return lhs->cost() > rhs->cost();
}

EuclidianComparison::EuclidianComparison(const bool& revparam)
{
  _reverse = revparam;
}

bool
EuclidianComparison::operator()(const boost::shared_ptr<Game> &lhs, const boost::shared_ptr<Game> &rhs) const
{
  return lhs->astar(Game::EUCLIDIAN) > rhs->astar(Game::EUCLIDIAN);
}

CanberraComparison::CanberraComparison(const bool& revparam)
{
  _reverse = revparam;
}

bool
CanberraComparison::operator()(const boost::shared_ptr<Game> &lhs, const boost::shared_ptr<Game> &rhs) const
{
  return lhs->astar(Game::CANBERRA) > rhs->astar(Game::CANBERRA);
}

KnightComparison::KnightComparison(const bool& revparam)
{
  _reverse = revparam;
}

bool
KnightComparison::operator()(const boost::shared_ptr<Game> &lhs, const boost::shared_ptr<Game> &rhs) const
{
  return lhs->astar(Game::KNIGHT) > rhs->astar(Game::KNIGHT);
}

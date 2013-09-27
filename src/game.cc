#include <ai-ucs/game.h>

#include <string.h>
#include <string>
#include <iostream>
#include <fstream>

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

boost::shared_ptr<Game>
Game::load(std::string filename)
{
  int size, x1, y1, x2, y2;
  std::ifstream f;
  f.open(filename.c_str());

  f >> size;
  f >> x1;
  f >> y1;
  f >> x2;
  f >> y2;

  f.close();

  boost::shared_ptr<Game> g(new Game(size, size, x1, y1, x2, y2));
  return g;
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
  switch (m) {
    case Game::RIGHT:
      return 5;
    case Game::LEFT:
      return 4;
    case Game::DOWN:
      return 6;
    case Game::UP:
      return 3;
  }

  return -1000;
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

  f << _history[0].size() << "\n";

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

bool
Game::move_player(int player, Game::Move m)
{
  if (m == Game::RIGHT && _players[player][0] < _w) {
    _players[player][1]++;
  } else if (m == Game::LEFT && _players[player][0] > 1) {
    _players[player][1]--;
  } else if (m == Game::DOWN && _players[player][1] < _h) {
    _players[player][0]++;
  } else if (m == Game::UP && _players[player][1] > 1) {
    _players[player][0]--;
  } else {
    return false;
  }

  return true;
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

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

void
Game::move(Game::Move m)
{
  // first, throw the current position into
  // the history vector
  save_to_history();
  move_player(0, m);
  if (m == Game::RIGHT) {
    move_player(1, Game::DOWN);
  } else if (m == Game::LEFT) {
    move_player(1, Game::UP);
  } else if (m == Game::DOWN) {
    move_player(1, Game::LEFT);
  } else if (m == Game::UP) {
    move_player(1, Game::RIGHT);
  }

  _cost += move_cost(m);
}

int
Game::move_cost(Game::Move m)
{
  int costs[4] = {
    5, /* RIGHT */
    4, /* LEFT */
    6, /* DOWN */
    3  /* UP */
  };

  return costs[m];
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
Game::move_player(int player, Game::Move m)
{
  if (m == Game::RIGHT && _players[player][0] < _w) {
    _players[player][0]++;
  } else if (m == Game::LEFT && _players[player][0] > 1) {
    _players[player][0]--;
  } else if (m == Game::DOWN && _players[player][1] < _h) {
    _players[player][1]++;
  } else if (m == Game::UP && _players[player][1] > 1) {
    _players[player][1]--;
  }
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
  return lhs.get()->cost() <= rhs.get()->cost();
}

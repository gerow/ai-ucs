#include <ai-ucs/game.h>

#include <string.h>
#include <string>
#include <iostream>
#include <fstream>

Game::Game()
{
  _w = _h = 0;
  memset(_players, 0, sizeof _players);
}

Game::Game(int w, int h, int x1, int y1, int x2, int y2) :
  _w(w),
  _h(h)
{
  memset(_players, 0, sizeof _players);

  _players[0][0] = x1;
  _players[0][1] = y1;
  _players[1][0] = x2;
  _players[1][1] = y2;
}

Game::Game(Game &g) :
  _w(g._w),
  _h(g._h)
{
  memcpy(_players, g._players, sizeof _players);
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
  return _players[0][0] == _players[1][0] &&
         _players[0][1] == _players[1][1];
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
  return _players[0][0];
}

int
Game::y1()
{
  return _players[0][1];
}

int
Game::x2()
{
  return _players[1][0];
}

int
Game::y2()
{
  return _players[1][1];
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

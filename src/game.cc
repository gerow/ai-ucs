#include <game.h>

Game::Game(int w, int h, int x1, int y1, int x2, int y2) :
  _w(w),
  _h(h)
{
  _players[0][0] = x1;
  _players[0][1] = y1;
  _players[1][0] = x2;
  _players[1][1] = y2;
}

void Game::move(Game::Move m)
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

int Game::move_cost(Game::Move m)
{
  int costs[4] = {
    5, /* RIGHT */
    4, /* LEFT */
    6, /* DOWN */
    3  /* UP */
  };

  return costs[m];
}

void Game::move_player(int player, Game::Move m)
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

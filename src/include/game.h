#ifndef _GAME_H
#define _GAME_H

class Game {
  public:
  	Game(int w, int h, int x1, int y1, int x2, int y2);

    Game(Game &g);

    enum Move { RIGHT, LEFT, DOWN, UP };

    void
    move(Move m);

    int
    move_cost(Move m);

    bool
    is_game_won();

    int
    w();

    int
    h();

    int
    x1();

    int
    y1();

    int
    x2();

    int
    y2();
  private:
    int _w, _h;

    int _players[2][2];

    void
    move_player(int player, Move m);
};

#endif /* _GAME_H */


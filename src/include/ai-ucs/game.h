#ifndef _GAME_H
#define _GAME_H

#include <string>
#include <vector>
#include <queue>

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>

typedef boost::numeric::ublas::vector<int> player_vector;

class Game {
  public:
    Game();

  	Game(int w, int h, int x1, int y1, int x2, int y2);

    Game(Game &g);

    enum Move { RIGHT, LEFT, DOWN, UP };

    static boost::shared_ptr<Game>
    load(std::string filename);

    bool
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

    double
    x1d();

    int
    y1();

    double
    y1d();

    int
    x2();

    double
    x2d();

    int
    y2();

    double
    y2d();

    //std::vector<boost::shared_ptr<player_vector> >
    //history();

    bool
    state_in_history(int x1, int y1, int x2, int y2);

    int
    cost();

    void
    save(std::string filename);

    void
    save_no_solution(std::string filename);

    double
    euclidian_distance();

    double
    canberra_distance();

    double
    knight_distance();
  private:
    int _w, _h;

    player_vector
    _players[2];

    std::vector<boost::shared_ptr<player_vector> >
    _history[2];

    int _cost;

    bool
    move_player(int player, Move m);

    void
    save_to_history();
};

class GameComparison {
  bool _reverse;
public:
  GameComparison(const bool& revparam=false);

  bool operator()(const boost::shared_ptr<Game> &lhs, const boost::shared_ptr<Game> &rhs) const;
};

typedef std::priority_queue<boost::shared_ptr<Game>, std::vector<boost::shared_ptr<Game> >, GameComparison> game_priority_queue;

#endif /* _GAME_H */

